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

//#define DISABLE_CAL_RESET
#define USE_ADC_LOOP
//#define USE_OWN_ADC
//#define DEBUG_ADC
//#define USE_PWM_LIMIT

// constants
#define PWM_LOW 1
#define PWM_MAX 235     // Not 255 due to FET Bootstrap capacitor charge
#define PWMHI_DIV 6
#define PWMLO_DIV 15
#define CLM358_DIFF 0
#define INC_PWM_MAX 1
#define ADC_MAX_LOOP 2
#define INC_PWM_MIN 0
#define UPDATE_INT 50

byte TICK_1000, VOL_PWM, LED1_tm;
unsigned int adc_vol, adc_cur, offset_cur, adc_prev, adc_diff;
unsigned long power_prev, power_curr, power_diff;
byte i, LM358_diff;
boolean flag_inc, got_max, main_continue;
byte Inc_pwm, eq_cnt;
byte vol1, vol2, lo_PWM, hi_PWM;
unsigned int wPWM, wTemp;
unsigned long prevtime, currtime, udtime;

// pin 
#define AREF PIN_B0
#define PWM PIN_B1
#define ADC_CUR_PIN PIN_B2
#define ADC_VOL_PIN PIN_B4
#define LED PIN_B3
#ifdef USE_OWN_ADC
  #define ADC_CUR 1
  #define ADC_VOL 2
#else
  #define ADC_CUR A1
  #define ADC_VOL A2
#endif

#ifdef USE_OWN_ADC 
  // 00 = PB5, 01 = PB2, 10 = PB4, 11 = PB3
int _AnalogRead(int port)
{
  port &= 3;
  ADMUX &= (~3);
  ADMUX |= port;
  ADCSRA |= (1<<ADEN) | (1<<ADSC);
  while(ADCSRA & (1<<ADSC)) ;
int ret=ADCL | (ADCH << 8);
  ADCSRA &= ~(1<<ADEN);  
  return ret;
}
#endif

void setup() {
  // ADC current
  pinMode(ADC_CUR_PIN, INPUT);
  // ADC Voltage
  pinMode(ADC_VOL_PIN, INPUT);
  pinMode(AREF, INPUT);
#ifdef USE_OWN_ADC
  ADMUX = (1<<REFS0) | (1<<MUX0) ;
  _AnalogRead(ADC_CUR);
#else
  analogReference(EXTERNAL);
  analogRead(ADC_CUR);  // prevent short
#endif

  pinMode(PWM, OUTPUT);
  // Timer1 PWM, 4KHz - FET Bootstrap don't work with higher clock.
  PLLCSR |= (1<<PLLE);
  while ((PLLCSR & (1<<PLOCK)) == 0x00)
    {
        // Do nothing
    }
  PLLCSR |= (1<<PCKE);
  GTCCR |= (1<<COM1B1) | (1<<COM1B0);  // fix bug
  TCCR1 = (1<<CTC1)    |  // Enable PWM
          (1<<CS12)    |  // PCK/64
          (1<<CS11)    |
          (1<<CS10)    |
          (1<<COM1A0)  |
          (1<<COM1A1);    // inverting mode
  TCCR1 |= (1<<PWM1A);
  //TIMSK = (1<<OCIE1A) | (1<<TOIE1);
  OCR1A = 0;
  OCR1C = 255;
  
  // LED
  pinMode(LED, OUTPUT);

  // init
  LED1_tm = 500;
  VOL_PWM = 0;
  TICK_1000 = 0;

  LM358_diff = CLM358_DIFF;

#ifndef DISABLE_CAL_RESET
  if(MCUSR & (1<<EXTRF)) {
    delay(500);    
#ifdef USE_OWN_ADC
    adc_cur = _AnalogRead(ADC_CUR);
#else
    adc_cur = analogRead(ADC_CUR);
#endif
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
#endif

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  vol1 = 0;
  vol2 = 0;

  OCR1A = PWM_LOW;
  lo_PWM = PWM_LOW;
  hi_PWM = PWM_MAX;
  flag_inc = true;
  adc_prev = 0; 
  prevtime = millis();
  udtime = micros();
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
  if(currtime - udtime < UPDATE_INT)
    goto CONTINUE;
  udtime = currtime;
  if(OCR1A>=PWM_MAX)
    LED1_tm = 127;
    else
      LED1_tm = 250;
  // save previous adc values
  power_prev = power_curr;
  adc_prev = adc_cur;
  // read adc value
#ifdef USE_ADC_LOOP  
  adc_vol = 0;
  adc_cur = 0;
  for(i=0;i<ADC_MAX_LOOP;i++) {
#ifdef USE_OWN_ADC
    adc_cur += (unsigned int) _AnalogRead(ADC_CUR);
    adc_vol += (unsigned int) _AnalogRead(ADC_VOL);
#else    
    adc_cur += (unsigned int) analogRead(ADC_CUR);
    adc_vol += (unsigned int) analogRead(ADC_VOL);
#endif
  }
  adc_vol = adc_vol / ADC_MAX_LOOP;
  adc_cur = adc_cur / ADC_MAX_LOOP;
#else
  #ifdef USE_OWN_ADC
    adc_cur = (unsigned int) _AnalogRead(ADC_CUR);
    adc_vol = (unsigned int) _AnalogRead(ADC_VOL);
  #else
    adc_cur = (unsigned int) analogRead(ADC_CUR);
    adc_vol = (unsigned int) analogRead(ADC_VOL);
  #endif  
#endif

#ifdef DEBUG_ADC
  currtime = millis();
  if(currtime - udtime > 5000) {
    EEPROM.write(4,highByte(adc_cur));
    EEPROM.write(5,lowByte(adc_cur));
    EEPROM.write(6,highByte(adc_vol));
    EEPROM.write(7,lowByte(adc_vol));
    udtime = currtime;
  }
#endif
  if(adc_cur>=LM358_diff) {
    power_curr = adc_cur * adc_vol;
    if(power_curr==power_prev) {
      Inc_pwm = INC_PWM_MIN;
      if(adc_cur>adc_prev)
        flag_inc = false;
      else if(adc_cur<adc_prev)
        flag_inc = true;
      else 
        flag_inc = !flag_inc;
      vol2 = 0;
      LED1_tm = 500;
      goto CONTINUE;
    } else {
      if(Inc_pwm<INC_PWM_MAX)
        ++Inc_pwm;
      if(power_curr<power_prev) {
        // vol1 = last low PWM
        flag_inc = !flag_inc;
/*
        // if set last low and high PWM, make average
        if(vol2!=0 || vol1!=0) {
          if(vol1==0)
            vol1=OCR1A;
          if(vol2==0)
            vol2=OCR1A;
          Inc_pwm = INC_PWM_MIN;
          wPWM = vol1;
          wPWM = (wPWM+vol2+1) / 2;
          if(highByte(wPWM)!=0 || lowByte(wPWM)>PWM_MAX)
            wPWM = (unsigned int)PWM_MAX;
          else if(lowByte(wPWM)<PWM_LOW)
            wPWM = (unsigned int)PWM_LOW;
          OCR1A = lowByte(wPWM);
          vol2 = 0;
          vol1 = 0;
          //
#ifdef USE_PWM_LIMIT          
          wPWM = (unsigned int)(PWM_MAX-OCR1A)+((PWMHI_DIV+1) / 2) / PWMHI_DIV;
          wPWM += (unsigned int)OCR1A;
          if(highByte(wPWM)!=0 || lowByte(wPWM)>PWM_MAX)
            wPWM = PWM_MAX;
          hi_PWM = lowByte(wPWM);
          //
          wPWM = (unsigned int)(OCR1A-PWM_LOW)+((PWMLO_DIV+1) / 2) / PWMLO_DIV;
          wPWM = (unsigned int)OCR1A - wPWM;
          if(highByte(wPWM)!=0 || lowByte(wPWM)<PWM_LOW)
            wPWM = PWM_LOW;
          lo_PWM = lowByte(wPWM);
#endif
          LED1_tm = 500;
          goto CONTINUE;
        }
*/
      } else {
        // last High PWM
        vol2 = OCR1A;
      }
    }
  } else {
    // no load or low current
    power_curr = 0;
    Inc_pwm = INC_PWM_MAX;
    flag_inc = true;
    vol2 = 0;
    vol1 = 0;
    lo_PWM = PWM_LOW;
    hi_PWM = PWM_MAX;
    LED1_tm = 80;
  }
CONT_PWM:
  // PWM
  if(flag_inc) {
    if(OCR1A<=(hi_PWM-Inc_pwm))
      OCR1A += Inc_pwm;
        else {
          vol2 = OCR1A;
          OCR1A = lo_PWM;
        }
  } else {
    if(OCR1A-lo_PWM>=(INC_PWM_MAX+1-Inc_pwm))
      OCR1A -= (INC_PWM_MAX+1-Inc_pwm);
      else {
        vol1 = OCR1A;
        OCR1A = hi_PWM;
      }
  }
CONTINUE:
  ;
}
