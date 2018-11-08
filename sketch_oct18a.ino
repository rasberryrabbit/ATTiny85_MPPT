/*
  simple MPPT with ATTiny85 by rasberryrabbit @ github
  
  It need ATTinycore. https://github.com/SpenceKonde/ATTinyCore

  it works 1MHz clock.
 */

#include <ATTinyCore.h>
#include <EEPROM.h>

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
#define PWM_MIN 1
#define PWM_MAX 250    // Not 255 due to FET Bootstrap capacitor charge
#define PWM_MID ((PWM_MAX-PWM_MIN)>>1)
#define CLM358_DIFF 0
#define INC_PWM_MAX 1
#define ADC_MAX_LOOP 2
#define INC_PWM_MIN 0
#define LOW_CURRENT (24/6)  // 12mA (base 6 mA)
#define _UPDATE_INT 250
#define VOLMUL ((int)25/6)  // Voltage vs Current = 25V(1024) / 6A(1024)
#define CURTOL 15          // 6 / 1024 * 15 = 87mA
#define VOLTOL 70*VOLMUL    // 25 / 1024 * 70 = 1.7v

byte LED1_tm;
int adc_vol, adc_cur, vol_prev, cur_prev1, cur_prev2, power_vol;
long power_prev, power_curr, power_temp;
byte i, LM358_diff;
boolean flag_inc, p_equal, up1, up2;
byte PWM_old, inc_pwm, pwm_power, pequal_cnt, pwm_low;
long prevtime, currtime, udtime, powertime, update_int;
int power_flag;

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

  pinMode(PWM, OUTPUT);
  // Timer1 PWM, 4KHz - FET Bootstrap don't work with higher clock.
  PLLCSR |= (1<<PLLE);
  while ((PLLCSR & (1<<PLOCK)) == 0x00)
    {
        // Do nothing
    }
  PLLCSR |= (1<<PCKE);
  OCR1A = 0;
  OCR1C = 255;
  TCCR1 = (1<<CTC1)    |  // Enable PWM
          (1<<PWM1A)   |
          (1<<CS12)    |  // PCK/64
          (1<<CS11)    |
          (1<<CS10)    |
          (1<<COM1A0)  |
          (1<<COM1A1);    // inverting mode
  
  // LED
  pinMode(LED, OUTPUT);

  // init
  LED1_tm = 500;

  LM358_diff = CLM358_DIFF;

// calibration @ reset
  if(MCUSR & (1<<EXTRF)) {
    delay(500);    
    adc_cur = analogRead(ADC_CUR);
    EEPROM.write(0,lowByte(adc_cur));
    // EEPROM Write
    delay(100);
    digitalWrite(LED,1);
    delay(700);
    digitalWrite(LED,0);
  }  
  delay(100);
  LM358_diff = EEPROM.read(0);
  if(LM358_diff>0x3f)
    LM358_diff=0;

  delay(500);

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  power_temp = 0;
  power_flag = 0;
  power_vol = 0;
  inc_pwm = 1;
  update_int = _UPDATE_INT;
  
  prevtime = millis();
  powertime = prevtime;
  udtime = millis();

  flag_inc = false;
  OCR1A = PWM_MAX;
  delay(300);
}

void debug_led() {
  digitalWrite(LED,1);
  delay(100);
  digitalWrite(LED,0);
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
  currtime = micros();
  // long delay at low PWM
  if(currtime - udtime < update_int)
    goto CONTINUE;
  udtime = currtime;
  if(OCR1A>=PWM_MAX)
    LED1_tm = 200;
  // save previous adc values
  power_prev = power_curr;
  vol_prev = adc_vol;
  cur_prev2 = cur_prev1;
  cur_prev1 = adc_cur;
  // get voltage, current
  adc_cur = 0;
  adc_vol = 0;
  for(i=0;i<ADC_MAX_LOOP;i++) {
    // read adc value
    adc_cur += analogRead(ADC_CUR);
    adc_vol += analogRead(ADC_VOL);
  }
  adc_cur /= ADC_MAX_LOOP;
  adc_vol /= ADC_MAX_LOOP;
  adc_vol *= VOLMUL;
  // get power
  power_curr = adc_cur * adc_vol;

  // active condition
  if(adc_cur > LM358_diff) {
    // avoid i(short circuit) condition for high voltage
int ctemp1 = abs(adc_cur-cur_prev1);
    if(ctemp1<CURTOL) {
      flag_inc = false;
      goto CONT_PWM;
    }
int ctemp2 = abs(power_vol-adc_vol);
    // check power
    if(power_curr > power_prev) {
      if(ctemp2>VOLTOL)
        power_temp = 0;
      LED1_tm = 500;
      if(power_temp < power_curr) {
        power_temp = power_curr;
        power_vol = adc_vol;
        pwm_power = OCR1A;
      }
      power_flag = 0;
    } else if(power_curr < power_prev) {
      LED1_tm = 400;
      if(ctemp1>CURTOL)
        flag_inc = !flag_inc;
      if((power_vol > VOLTOL) && (adc_vol<power_vol-VOLTOL))
        power_temp = 0;
      power_flag = -1;
    } else {
      // reset maxium power
      if(ctemp2>VOLTOL)
        power_temp = 0;
    }
  } else {
    LED1_tm = 300;
    // low current
    OCR1A = PWM_MAX;
    flag_inc = false;
    power_curr = 0;
    power_flag = 0;
    adc_cur = 0;
    cur_prev1 = 0;

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
