/*
  simple MPPT with ATTiny85 by rasberryrabbit @ github
  
  It need ATTinycore. https://github.com/SpenceKonde/ATTinyCore
  
 */

#include <EEPROM.h> 

//#define DISABLE_CAL
#define DISABLE_INCPWM

// constants
#define PWM_LOW 2
#define PWM_MAX 255
#define PWMHI_DIV 6
#define PWMLO_DIV 15
#define CLM358_DIFF 0
#define INC_PWM_MAX 8
#define ADC_MAX_LOOP 1

byte TICK_1000, VOL_PWM, LED1_tm;
word adc_vol, adc_cur, offset_cur, adc_prev, adc_diff;
unsigned long power_prev, power_curr, power_diff;
byte i, LM358_diff;
boolean flag_inc, got_max, main_continue;
byte Inc_pwm, eq_cnt;
byte vol1, vol2, lo_PWM, hi_PWM;
byte IncPWM_EQ;
word wPWM, wTemp;
unsigned long prevtime, currtime;

// pin 
#define AREF 0
#define PWM 1
#define ADC_CUR 2
#define LED 3
#define ADC_VOL 4
#define OCAL 5  // disable reset on FUSE

void setup() {
  // AREF
  pinMode(AREF, INPUT);
  analogReference(EXTERNAL);
  analogRead(ADC_CUR);  // prevent short

  cli();

  pinMode(PWM, OUTPUT);
  /* 
  // Timer0 PWM, Fast PWM, OC0B non-inverting
  TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0B1);
  TCCR0B |= (1<<CS00);
  OCR0B = 0;
  */

  // Timer1 PWM, 128KHz
  PLLCSR |= (1<<PLLE);
  while ((PLLCSR & (1<<PLOCK)) == 0x00)
    {
        // Do nothing until plock bit is set
    }
  PLLCSR |= (1<<PCKE);
  TCCR1 = (1<<CTC1)    | // Enable PWM
          (1<<PWM1A)   | // Set source to pck
          (1<<(CS11))  | // PCK/2
          (1<<COM1A1);   // Clear the OC1A output line.
  OCR1C = PWM_MAX;
  TIMSK = (1<<OCIE1A);
  OCR1A = 0;

  sei();
  
  // ADC current
  pinMode(ADC_CUR, INPUT);
  
  // LED
  pinMode(LED, OUTPUT);
  
  // ADC Voltage
  pinMode(ADC_VOL, INPUT);

#ifndef DISABLE_CAL  
  // OPAMP Cal. Set FUSE disable RESET
  pinMode(OCAL, INPUT);
#endif

  // init
  LED1_tm = 500;
  VOL_PWM = 0;
  TICK_1000 = 0;

  LM358_diff = CLM358_DIFF;
  delay(100);

#ifndef DIABLE_CAL  
  if(digitalRead(OCAL)==0) {
    delay(300);
    adc_cur = analogRead(ADC_CUR);
    EEPROM.write(0,lowByte(adc_cur));
  }
  delay(100);
  LM358_diff = EEPROM.read(0);
#else
  adc_cur = analogRead(ADC_CUR);
  LM358_diff = lowByte(adc_cur);
#endif

  IncPWM_EQ = 0;
#ifndef DISBALE_INCPWM  
  IncPWM_EQ = EEPROM.read(3);
#endif

  adc_vol = 0;
  adc_cur = 0;
  power_curr = 0;
  vol1 = 0;
  vol2 = 0;
  prevtime = millis();

  VOL_PWM = PWM_LOW;
  lo_PWM = PWM_LOW;
  hi_PWM = PWM_MAX;
  flag_inc = true;
  adc_prev = 0; 
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
  adc_vol = 0;
  adc_cur = 0;
  for(i=0;i<ADC_MAX_LOOP;i++) {
    adc_cur += analogRead(ADC_CUR);
    adc_vol += analogRead(ADC_VOL);
  }
  adc_vol = adc_vol / ADC_MAX_LOOP;
  adc_cur = adc_cur / ADC_MAX_LOOP;
  // sub op-amp offset value
  if(adc_cur>LM358_diff)
    adc_cur -= LM358_diff;
    else
      adc_cur = 0;
  //
  if(adc_cur>0) {
    if(lo_PWM==0)
      lo_PWM = VOL_PWM;
    power_curr = adc_cur * adc_vol;
    if(power_curr==power_prev) {
      Inc_pwm = 0;
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
          Inc_pwm = 0;
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
    if(VOL_PWM-lo_PWM > INC_PWM_MAX+1-Inc_pwm)
      VOL_PWM -= (INC_PWM_MAX+1-Inc_pwm);
    else
      VOL_PWM = lo_PWM;
  }
CONTINUE:
  /* OCR0B = VOL_PWM; */
  OCR1A = VOL_PWM; 
}
