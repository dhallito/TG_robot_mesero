#include "motor.h"

void iniciar_motores(){
  /* Pines setup */
  pinMode(enableA_pin, OUTPUT);
  pinMode(input1_pin, OUTPUT);
  pinMode(input2_pin, OUTPUT);
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(enableB_pin, OUTPUT);
  pinMode(input3_pin, OUTPUT);
  pinMode(input4_pin, OUTPUT);
  pinMode(encoderB, INPUT_PULLUP);
}

void adelante_motorA(){
  digitalWrite(input1_pin, HIGH);
  digitalWrite(input2_pin, LOW);
}

void atras_motorA(){
  digitalWrite(input1_pin, LOW);
  digitalWrite(input2_pin, HIGH);
}

void detener_motorA(){
  digitalWrite(input1_pin, LOW);
  digitalWrite(input2_pin, LOW);
  ledcWrite(canal1_pwm, 255);
  last_timeA = 0;   /*Ultimo tiempo de motor */
  revolucionA_time = 0;
  rpm_motorA = 0;
  rads_motorA = 0;
  setpoint_rpm_motorA = 0;
  ek_motorA[0] = 0;
  ek_motorA[1] = 0;
  ck_motorA[0] = 0;
  ck_motorA[1] = 0;
}

void controlar_motorA(int ck){
  int pwm_A = ck;
  if (pwm_A < 0){
    pwm_A = 0;
  }else if(pwm_A > 255){
    pwm_A = 255;
  }
  pwm_A = -pwm_A + 255;
  ledcWrite(canal1_pwm, pwm_A);
  
}


void adelante_motorB(){
  digitalWrite(input3_pin, LOW);
  digitalWrite(input4_pin, HIGH);
}

void atras_motorB(){
  digitalWrite(input3_pin, HIGH);
  digitalWrite(input4_pin, LOW);
}

void detener_motorB(){
  digitalWrite(input3_pin, LOW);
  digitalWrite(input4_pin, LOW);
  ledcWrite(canal2_pwm, 255);
  last_timeB = 0;   /*Ultimo tiempo de motor */
  revolucionB_time = 0;
  rpm_motorB = 0;
  rads_motorB = 0;
  setpoint_rpm_motorB = 0;
  ek_motorB[0] = 0;
  ek_motorB[1] = 0;
  ck_motorB[0] = 0;
  ck_motorB[1] = 0;
}

void controlar_motorB(int ck){
  int pwm_B = ck;
  if (pwm_B < 0){
    pwm_B = 0;
  }else if(pwm_B > 255){
    pwm_B = 255;
  }
  pwm_B = -pwm_B + 255;
  ledcWrite(canal2_pwm, pwm_B);
}
