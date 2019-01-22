/*
  simple MPPT with ATTiny85 by rasberryrabbit @ github
  
  It need ATTinycore. https://github.com/SpenceKonde/ATTinyCore

  [Tool Option]
  Clock = 1MHz internal, BOD disabled, EEPROM retained, Timer1 clock = CPU, LTO disabled,
  No Bootloader.
 */

#include <ATTinyCore.h>
#include <EEPROM.h>
#include <avr/wdt.h>

/* re-define Reference for ATTiny x5, bug fix */
// X 0 0 VCC used as Voltage Reference, disconnected from PB0 (AREF).
#define DEFAULT (B0000)
// X 0 1 External Voltage Reference at PB0 (AREF) pin, Internal Voltage Reference turned off.
#define EXTERNAL (B0100)
// 0 1 0 Internal 1.1V Voltage Reference.
#define INTERNAL (B1000)
#define INTERNAL1V1 INTERNAL
// 1 1 1 Internal 2.56V Voltage Reference with external bypass capacitor at PB0 (AREF) pin(1).
#define INTERNAL2V56 (B1101)
// 1 1 0 Internal 2.56V Voltage Reference without external bypass capacitor, disconnected from PB0 (AREF)(1).
#define INTERNAL2V56_NO_CAP (B1001)
#define INTERNAL2V56NOBP INTERNAL2V56_NO_CAP

// constants
#define PWM_MIN 1                     // 10%
#define PWM_MAX 250                   // 90%
#define PWM_MID (PWM_MAX+PWM_MIN)/2
#define PWM_CHECK PWM_MID
#define PWM_CHECK_TIME 4500          // 4.5sec
#define CLM358_DIFF 0
#define INC_PWM_MAX 1
#define ADC_MAX_LOOP 5  // 3~6
#define INC_PWM_MIN 0
#define _UPDATE_INT 30
#define _CUR_LIMIT 12  // 0.04V / 3.6 * 1024
#define _UPDATE_VOL 1
#define VOLMUL ((int)25/6)  // Voltage vs Current = 25V(1024) / 6A(1024)

#define USE_PLL

int LED1_tm;
int adc_cur, cur_prev, adc_vol, vol_prev1, vol_prev2, cur_power, vol_power, vol_last;
long power_prev, power_curr;
byte i, LM358_diff, streg;
boolean flag_inc, p_equal, wdtreset;
byte inc_pwm, pwm_power;
long prevtime, currtime, udtime, powertime, update_int;
byte power_flag, doADCRead;

const char wdtdetect[] = "wdtreset";
char *p = (char *) malloc(sizeof(wdtdetect));

bool CheckWDT() {
  return(strcmp(p, wdtdetect) == 0);
}

// pin 
#define AREF PIN_B0
#define PWM PIN_B1
#define ADC_CUR_PIN PIN_B2
#define ADC_VOL_PIN PIN_B4
#define LED PIN_B3
#define ADC_CUR A1
#define ADC_VOL A2

void setup() {
  // ADC current
  pinMode(ADC_CUR_PIN, INPUT);
  // ADC Voltage
  pinMode(ADC_VOL_PIN, INPUT);
  pinMode(AREF, INPUT);
  analogReference(EXTERNAL);
  analogRead(ADC_CUR);  // prevent short

  wdtreset = CheckWDT();
  p[0]=0;
  MCUSR &= ~(1<<WDRF);
  WDTCR = (1<<WDE) | (1<<WDCE);
  WDTCR = (1<<WDE) | (1<<WDIE) | (1<<WDP3);    // 4 seconds watchdog

  pinMode(PWM, OUTPUT);
  // Timer1 PWM, 8KHz - FET Bootstrap don't work with higher clock.
  PLLCSR |= (1<<PLLE) | (1<<LSM);
  delayMicroseconds(200);
  while ((PLLCSR & (1<<PLOCK)) == 0x00)
    {
        // Do nothing
    }
  PLLCSR |= (1<<PCKE);
  OCR1A = 0;
  OCR1C = 255;
  TCCR1 = (1<<CTC1)    |  // Enable PWM
          (1<<PWM1A)   |
          (1<<CS12)    |  // PCK/16
          //(1<<CS11)    |
          (1<<CS10)    |
          (1<<COM1A0)  |
          (1<<COM1A1);    // inverting mode
  
  // LED
  pinMode(LED, OUTPUT);

  // init
  LED1_tm = 500;

  LM358_diff = CLM358_DIFF;
  wdt_reset();

// calibration @ reset
  if((MCUSR & (1<<EXTRF)) && (!wdtreset)) {
    delay(500);    
    adc_cur = analogRead(ADC_CUR);
    EEPROM.write(0,lowByte(adc_cur));
    // EEPROM Write
    delay(100);
    digitalWrite(LED,1);
    delay(700);
    digitalWrite(LED,0);
    wdt_reset();
  }  
  delay(100);
  LM358_diff = EEPROM.read(0);
  if(LM358_diff>0x3f)
    LM358_diff=0;

  delay(500);

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  cur_power = 0;
  inc_pwm = 1;
  update_int = _UPDATE_INT;
  power_flag = 1;
  vol_power = 0;
  
  prevtime = millis();
  powertime = prevtime;
  udtime = prevtime;
  

  flag_inc = false;
  OCR1A = PWM_MID;
  delay(300);
  sei();
}

void debug_led() {
  digitalWrite(LED,1);
  delay(100);
  digitalWrite(LED,0);
}

bool check_vdiff(int a,int b, int c) {
  return (c+a+1)/2<b;
}

void loop() {
  // LED
  currtime = millis();
  if(currtime - prevtime >= LED1_tm) {
    prevtime = currtime;
    boolean lv=digitalRead(LED);
    if(lv)
      digitalWrite(LED,LOW);
      else
        digitalWrite(LED,HIGH);
  }
  // get voltage, current
  vol_prev2 = vol_prev1;
  vol_prev1 = adc_vol;
  cur_prev = adc_cur;
  // wait timer1 overflow
  while(bitRead(TIFR,TOV1)==0) ;
  // get voltage, current
  adc_cur = analogRead(ADC_CUR);
  adc_vol = analogRead(ADC_VOL);
int temp1, temp2;
  for(i=0;i<ADC_MAX_LOOP-1;i++) {
    // read adc value
    temp2 = analogRead(ADC_CUR);
    temp1 = analogRead(ADC_VOL);
    adc_vol = (adc_vol+temp1) / 2;
    if(temp2 > adc_cur)
      adc_cur = temp2;
    //adc_cur = (adc_cur+temp2) / 2;
  }
  adc_vol *= VOLMUL;

  // long delay at low PWM
  currtime = millis();
  if(currtime - udtime < update_int)
    goto CONTINUE;
  wdt_reset();
  udtime = currtime;
  // save previous adc values
  power_prev = power_curr;

  // get power
  power_curr = (long) adc_cur * adc_vol;

  // avoid low voltage condition
  currtime = millis();
  if(OCR1A>PWM_CHECK) {
    if(currtime - powertime > PWM_CHECK_TIME) {
      powertime = currtime;
      adc_cur = LM358_diff; 
    }
  } else 
    powertime = currtime;

  // active condition
  if(adc_cur > LM358_diff) {
    power_flag = 1;
    if(power_curr == power_prev) {
      LED1_tm = 500;
      goto CONTINUE;
    } else if(power_curr > power_prev) {
      LED1_tm = 400;
    } else {
      LED1_tm = 300;
      flag_inc = !flag_inc;
    }
    /*
    if(check_vdiff(adc_vol,vol_prev1,vol_prev2))
      flag_inc = true;
    */
  } else {
    LED1_tm = 300;
    // low current
    OCR1A = PWM_MID;
    flag_inc = false;
    power_curr = 0;
    adc_cur = 0;
    cur_power = 0;
    power_flag = 1;
    vol_power = 0;

    goto CONTINUE;
  }

CONT_PWM:

  if(flag_inc) {
    if(OCR1A < PWM_MAX)
      ++OCR1A;
      else {
        OCR1A = PWM_MAX;
        flag_inc = false;
      }
  } else {
    if(OCR1A > PWM_MIN)
      --OCR1A;
      else {
        OCR1A = PWM_MIN;
        flag_inc = true;
      }
  }

CONTINUE:
  ;
}

ISR(WDT_vect) {
  memcpy(p, wdtdetect, sizeof(wdtdetect));    // store watdog signature
}
