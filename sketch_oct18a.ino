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
//#define USE_STALLCHECK

// constants
#define PWM_MIN 1
#define PWM_MAX 250     // Not 255 due to FET Bootstrap capacitor charge
#define CLM358_DIFF 0
#define INC_PWM_MAX 1
#define ADC_MAX_LOOP 2
#define INC_PWM_MIN 0
#define UPDATE_INT 10000
#define VOLMUL ((int)25/6)  // Voltage vs Current = 25V(1024) / 6A(1024)

byte LED1_tm;
unsigned int adc_vol, adc_cur, vol_prev, cur_prev, adc_tmp1, adc_tmp2;
unsigned long power_prev, power_curr;
byte i, LM358_diff;
boolean flag_inc, p_equal;
byte PWM_old, inc_pwm, pwm_power, pequal_cnt;
unsigned long prevtime, currtime, udtime, stallcheck;

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
  OCR1C = 255;
  OCR1A = 0;
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

#ifndef DISABLE_CAL_RESET
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
#endif
  ++LM358_diff;

  delay(500);

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  power_prev = 0;
  pequal_cnt = 0;
  pwm_power = PWM_MAX;
  inc_pwm = 1;
  
  OCR1A = PWM_MIN;

  flag_inc = true;
  p_equal = false;
  vol_prev = 0; 
  cur_prev = 0;
  PWM_old = 0;
  prevtime = millis();
  stallcheck = prevtime;
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
  vol_prev = adc_vol;
  cur_prev = adc_cur;
  // read adc value
#ifdef USE_ADC_LOOP  
  adc_vol = 0;
  adc_cur = 0;
  for(i=0;i<ADC_MAX_LOOP;i++) {
    adc_cur += analogRead(ADC_CUR);
    adc_vol += analogRead(ADC_VOL);
  }
  adc_cur /= ADC_MAX_LOOP;
  adc_vol /= ADC_MAX_LOOP;
#else
  adc_cur = analogRead(ADC_CUR);
  adc_vol = analogRead(ADC_VOL);
#endif
  adc_vol *= VOLMUL;

  // check OP_AMP offset
  if(adc_cur > LM358_diff) {
    // get power
    power_curr = (unsigned long) adc_vol * adc_cur;
    // check power
    if(power_curr == power_prev) {
      LED1_tm = 600;
      // Get High Voltage
      if(!p_equal || adc_cur == cur_prev) {
        if(adc_vol < vol_prev)
          flag_inc = true;
          else if(adc_vol > vol_prev)
            flag_inc = false;
        if(p_equal && adc_cur == cur_prev)
          flag_inc = !flag_inc;
      }
      // Get High Current
      if(p_equal || adc_vol == vol_prev) {
        if(adc_cur < cur_prev)
          flag_inc = false;
          else if(adc_cur > cur_prev)
            flag_inc = true;
        if((!p_equal) && adc_vol == vol_prev)
          flag_inc = !flag_inc;
      }
      p_equal = true;
    } else {
      LED1_tm = 400;
      if(power_curr < power_prev)
        flag_inc = !flag_inc;
        else {
          // save last low pwm
          if(pequal_cnt < 255)
            ++pequal_cnt;
          if(OCR1A < pwm_power)
            pwm_power = OCR1A;
        }
      p_equal = false;
    }
  } else {
    // reset parameter at zero current
    LED1_tm = 127;
    flag_inc = true;
    p_equal = false;
    power_curr = 0;
    power_prev = 0;
    inc_pwm = 1;
    adc_cur = 0;
    adc_vol = 0;
    // avoid zerp current
    if(pequal_cnt > 0)
      OCR1A = pwm_power;
    pwm_power = PWM_MAX;
    pequal_cnt = 0;
  }
CONT_PWM:
  if(flag_inc) {
    if(OCR1A < PWM_MAX-inc_pwm)
      OCR1A += inc_pwm;
      else {
        inc_pwm = 1;
        // set high voltage pwm
        if(pequal_cnt > 0) {
          OCR1A = pwm_power;
          pwm_power = PWM_MAX;
        } else {
          OCR1A = PWM_MAX;
          flag_inc = false;
        }
        pequal_cnt = 0;
      }
  } else {
    if(OCR1A > PWM_MIN+inc_pwm)
      OCR1A -= inc_pwm;
      else {
        inc_pwm = 1;
        // set high voltage pwm
        if(pequal_cnt > 0) {
          OCR1A = pwm_power;
          pwm_power = PWM_MAX;
        } else
            OCR1A = PWM_MIN;
        flag_inc = true;
        pequal_cnt = 0;
      }
  }
CONTINUE:
#ifdef USE_STALLCHECK
  currtime = millis();
  if(currtime - stallcheck > 3000) {
    stallcheck = currtime;
    if((!p_equal) && (PWM_old == OCR1A)) {
      OCR1A = PWM_MIN;
      flag_inc = true;
      power_curr = 0;
      adc_cur = 0;
      adc_vol = 0;
    }
    PWM_old = OCR1A;
  }
#else
  ;
#endif
}
