/*
  simple MPPT with ATTiny85 by rasberryrabbit @ github
  
  It need ATTinycore. https://github.com/SpenceKonde/ATTinyCore

  it works 1MHz clock.
 */

#include <ATTinyCore.h>
#include <EEPROM.h> 

//#define DISABLE_CAL_RESET
#define DISABLE_INCPWM
#define USE_ADC_LOOP

// constants
#define PWM_LOW 1
#define PWM_MAX 255
#define PWMHI_DIV 6
#define PWMLO_DIV 15
#define CLM358_DIFF 0
#define INC_PWM_MAX 1
#define ADC_MAX_LOOP 1
#define INC_PWM_MIN 0

byte TICK_1000, VOL_PWM, LED1_tm;
word adc_vol, adc_cur, offset_cur, adc_prev, adc_diff;
unsigned long power_prev, power_curr, power_diff;
byte i, LM358_diff;
boolean flag_inc, got_max, main_continue;
byte Inc_pwm, eq_cnt;
byte vol1, vol2, lo_PWM, hi_PWM;
byte IncPWM_EQ;
word wPWM, wTemp;
unsigned long prevtime, currtime, udtime;

// pin 
#define AREF PIN_B0
#define PWM PIN_B1
#define ADC_CUR A1
#define ADC_CUR_PIN PIN_B2
#define LED PIN_B3
#define ADC_VOL A2
#define ADC_VOL_PIN PIN_B4

void setup() {
  // ADC current
  pinMode(ADC_CUR_PIN, INPUT);
  // ADC Voltage
  pinMode(ADC_VOL_PIN, INPUT);
  // AREF
  pinMode(AREF, INPUT);
  analogReference(EXTERNAL);
  analogRead(ADC_CUR);  // prevent short

  pinMode(PWM, OUTPUT);
  // Timer1 PWM, 128KHz
  PLLCSR |= (1<<PLLE);
  while ((PLLCSR & (1<<PLOCK)) == 0x00)
    {
        // Do nothing
    }
  PLLCSR |= (1<<PCKE);
  TCCR1 = (1<<CTC1)    |  // Enable PWM
          (1<<PWM1A)   |  // Set source to pck
          (1<<CS11)    |  // PCK/2
          (1<<COM1A0)  |  // Invert PWM
          (1<<COM1A1);
  GTCCR |= (1<<COM1B1) | (1<<COM1B0);  // fix bug
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
  delay(300);

#ifndef DISABLE_CAL_RESET  
  if(MCUSR & (1<<EXTRF)) {
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
#endif

  IncPWM_EQ = 0;
#ifndef DISABLE_INCPWM  
  IncPWM_EQ = EEPROM.read(3);
#endif

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  vol1 = 0;
  vol2 = 0;

  VOL_PWM = PWM_LOW;
  lo_PWM = PWM_LOW;
  hi_PWM = PWM_MAX;
  flag_inc = true;
  adc_prev = 0; 
  OCR1A = PWM_LOW;
  prevtime = millis();
  udtime = prevtime;
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
  if(VOL_PWM>=(PWM_MAX-1)) 
    LED1_tm = 125;
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
    adc_cur += analogRead(ADC_CUR);
    adc_vol += analogRead(ADC_VOL);
  }
  adc_vol = adc_vol / ADC_MAX_LOOP;
  adc_cur = adc_cur / ADC_MAX_LOOP;
#else
  adc_cur = analogRead(ADC_CUR);
  adc_vol = analogRead(ADC_VOL);
#endif  
  // sub op-amp offset value
  if(adc_cur>LM358_diff)
    adc_cur -= LM358_diff;
    else
      adc_cur = 0;
  //
  if(adc_cur>0) {
    if(lo_PWM==0)
      lo_PWM = VOL_PWM;
    power_curr = (unsigned long) adc_cur * adc_vol;
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
        vol1 = VOL_PWM;
        flag_inc = !flag_inc;
        // if set last low and high PWM, make average
        if(vol2!=0) {
          Inc_pwm = INC_PWM_MIN;
          wPWM = vol1;
          wPWM = (wPWM+vol2+1) / 2 + 3;
          if(highByte(wPWM)!=0 || lowByte(wPWM)>PWM_MAX)
            wPWM = word(PWM_MAX);
          else if(lowByte(wPWM)<PWM_LOW)
            wPWM = word(PWM_LOW);
          VOL_PWM = lowByte(wPWM);
          
          vol2 = 0;
          //
          wPWM = word(PWM_MAX-VOL_PWM)+((PWMHI_DIV+1) / 2) / PWMHI_DIV;
          wPWM += word(VOL_PWM);
          if(highByte(wPWM)!=0 || lowByte(wPWM)>PWM_MAX)
            wPWM = PWM_MAX;
          hi_PWM = lowByte(wPWM);
          //
          wPWM = word(VOL_PWM-PWM_LOW)+((PWMLO_DIV+1) / 2) / PWMLO_DIV;
          wPWM = word(VOL_PWM) - wPWM;
          if(highByte(wPWM)!=0 || lowByte(wPWM)<PWM_LOW)
            wPWM = PWM_LOW;
          lo_PWM = lowByte(wPWM);
          goto CONTINUE;
        }
      } else {
        // last High PWM
        vol2 = VOL_PWM;
      }
    }
  } else {
    // no load or low current
    power_curr = 0;
    Inc_pwm = INC_PWM_MAX;
    flag_inc = true;
    vol2 = 0;
    lo_PWM = PWM_LOW;
    hi_PWM = PWM_MAX;
  }
  // PWM
  if(flag_inc) {
    if(VOL_PWM<(hi_PWM-Inc_pwm))
      VOL_PWM += Inc_pwm;
    else
      VOL_PWM = hi_PWM;
  } else {
    if(VOL_PWM-lo_PWM>(INC_PWM_MAX+1-Inc_pwm))
      VOL_PWM -= (INC_PWM_MAX+1-Inc_pwm);
      else
        VOL_PWM = lo_PWM;
  }
CONTINUE:
  OCR1A = VOL_PWM;
}
