#include "variables.h"
#include "maquina_estados.h"

/* Timer0: Muestreo */
bool muestreo_flag = false;
hw_timer_t * timer0 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer0(){   /* Funcion de interrupcion */
  muestreo_flag = true;
}

/* GPIO Interrupcion encoder A */
int encoderA_counter = 0;   /* Contador de encoder A*/
bool revolucionA_flag = false;
void IRAM_ATTR isr_encoderA() {
  encoderA_counter ++;
  if (encoderA_counter == 16){
    encoderA_counter = 0;
    revolucionA_flag = true;
  }
}

/* GPIO Interrupcion encoder B */
int encoderB_counter = 0;   /* Contador de encoder A*/
bool revolucionB_flag = false;
void IRAM_ATTR isr_encoderB() {
  encoderB_counter ++;
  if (encoderB_counter == 16){
    encoderB_counter = 0;
    revolucionB_flag = true;
  }
}




void setup() {
  Serial.begin(115200);

  maquina_estados(state);
  
  /* PWM setup */
  ledcSetup(canal1_pwm, F_pwm, resolucion);
  ledcAttachPin(enableA_pin, canal1_pwm);
  ledcSetup(canal2_pwm, F_pwm, resolucion);
  ledcAttachPin(enableB_pin, canal2_pwm);

  /* Timer 0 setup: Muestreo */
  timer0 = timerBegin(0, 80, true);    /*80MHz/80 = 1MHz -> 1 us */
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, T*1000, true);    /* Periodo de muestreo en us */
  timerAlarmEnable(timer0);

  /* GPIO Encoder A Interrupt */
  attachInterrupt(encoderA, isr_encoderA, RISING);

  /* GPIO Encoder B Interrupt */
  attachInterrupt(encoderB, isr_encoderB, RISING);
  
  nueva_ruta = true;
  ruta[0] = 'A';
  ruta[1] = 'C';  
  ruta[2] = 'D';
  ruta[3] = 'C';
  ruta[4] = 'B';
  ruta[5] = 'E';
  ruta[6] = 'B';
  ruta_size = 7;
  angulo_absoluto = 3.14;
  nodo_actual = 'A';
  detener_motorA();
  detener_motorB();
  delay(3000);
}

void loop() {
  maquina_estados(state);
  
  /* Calculo RPM Motor A */
  if (revolucionA_flag){
    revolucionA_flag = false;    
    revolucionA_time = (micros() - last_timeA)*RT;
    rpm_motorA = (1/revolucionA_time)*60000000;    /* Un minuto son 60000000 ms */
    rads_motorA = rpm_motorA*0.1047197551; /* Conversion a radianes por segundo */
    last_timeA = micros();
    distancia_ruedaA = distancia_ruedaA + (R*6.28319)/70; /* Conversion de rev a rad */
  }
  
  /* Calculo RPM Motor B */
  if (revolucionB_flag){
    revolucionB_flag = false;    
    revolucionB_time = (micros() - last_timeB)*RT;
    rpm_motorB = (1/revolucionB_time)*60000000;    /* Un minuto son 60000000 ms */
    rads_motorA = rpm_motorA*0.1047197551; /* Conversion a radianes por segundo */
    last_timeB = micros();
    distancia_ruedaB = distancia_ruedaB + (R*6.28319/70); /* Conversion de rev a rad */        
  }
  
  /* Envío de datos */
  if (muestreo_flag) {
    muestreo_flag = false;
    if (controlando){
      ek_motorA[1] = ek_motorA[1] + ek_motorA[0];
      ek_motorA[0] = setpoint_rpm_motorA - rpm_motorA;
      ek_motorB[1] = ek_motorB[1] + ek_motorB[0];
      ek_motorB[0] = setpoint_rpm_motorB - rpm_motorB;
      
      ck_motorA[0] = kp_motorA*ek_motorA[0]+ki_motorA*ek_motorA[1];
      controlar_motorA(ck_motorA[0]);
      
      ck_motorB[0] = kp_motorB*ek_motorB[0]+ki_motorB*ek_motorB[1];
      controlar_motorB(ck_motorB[0]); 
    }else{
      ledcWrite(canal1_pwm, 100);
      ledcWrite(canal2_pwm, 100);
    }
    
//    Serial.print(angulo_relativo);
//    Serial.print(',');
//    Serial.print(distancia_relativa);
//    Serial.print(',');
//    Serial.print(ek_motorA[0]);
//    Serial.print(',');
//    Serial.print(ck_motorA[0]);
//    Serial.print(',');
//    Serial.print(distancia_ruedaA);
//    Serial.print(',');
//    Serial.print(rpm_motorA);
//    Serial.print(',');
//    Serial.print(ek_motorB[0]);
//    Serial.print(',');
//    Serial.print(ck_motorB[0]);
//    Serial.print(',');
//    Serial.print(distancia_ruedaB);
//    Serial.print(',');
//    Serial.println(rpm_motorB);
  }
}
