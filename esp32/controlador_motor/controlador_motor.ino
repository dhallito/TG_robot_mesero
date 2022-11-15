#include <Arduino.h>

/* Muestreo */
int T = 100;    /* Periodo de muestreo en milisegundos */
int RT = 70;    /* Relación de transmisión */
unsigned long last_timeA = 0;   /*Ultimo tiempo de motor */
float revolucionA_time = 0;
float rpm_motorA = 0;
unsigned long last_timeB = 0;   /*Ultimo tiempo de motor */
float revolucionB_time = 0;
float rpm_motorB = 0;

/* PWM */
int F_pwm = 16000;    /* Frecuencia de PWM (Selección final = 16kHz */
int pwm = 5;    /* Valor PWM */
int canal1_pwm = 0;   /* Canal de PWM */
int canal2_pwm = 1;   /* Canal de PWM */
int resolucion = 8;   /* Resolución de 8 bits */
int change = 25;

/* Pines Motor A */
int enableA_pin = 12;
int input1_pin = 14;
int input2_pin = 27;
int encoderA = 13;

/* Pines Motor B */
int enableB_pin = 25;
int input3_pin = 32;
int input4_pin = 33;
int encoderB = 26; 

/* Timer0: Muestreo */
bool muestreo_flag = false;
hw_timer_t * timer0 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer0(){   /* Funcion de interrupcion */
  muestreo_flag = true;
}

/* Timer3: Cambios PWM */
bool cambio_pwm_flag = false;
hw_timer_t * timer3 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer3(){   /* Funcion de interrupcion */
  cambio_pwm_flag = true;
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

  /* Pines setup */
  pinMode(enableA_pin, OUTPUT);
  pinMode(input1_pin, OUTPUT);
  pinMode(input2_pin, OUTPUT);
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(enableB_pin, OUTPUT);
  pinMode(input3_pin, OUTPUT);
  pinMode(input4_pin, OUTPUT);
  pinMode(encoderB, INPUT_PULLUP);

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

  /* Timer 3 setup: PWM Change */
  timer3 = timerBegin(3, 80, true);    /*80MHz/80 = 1MHz -> 1 us */
  timerAttachInterrupt(timer3, &onTimer3, true);
  timerAlarmWrite(timer3, 1000000, true);    /* Periodo de muestreo en us */
  timerAlarmEnable(timer3);

  /* GPIO Encoder A Interrupt */
  attachInterrupt(encoderA, isr_encoderA, RISING);

  /* GPIO Encoder B Interrupt */
  attachInterrupt(encoderB, isr_encoderB, RISING);

  /* Encender motor A */
  digitalWrite(input1_pin, HIGH);
  digitalWrite(input2_pin, LOW); 

  /* Encender motor B */
  digitalWrite(input3_pin, HIGH);
  digitalWrite(input4_pin, LOW); 

  /* Inicio de datos */
  delay(1000);
}

void loop() {
  /* Cambio PWM */
  if (cambio_pwm_flag){
    cambio_pwm_flag = false;
    pwm = pwm + change;
    if (pwm > 255 or pwm < 5){
      change = change*(-1);
      pwm = pwm + change;
    }
    ledcWrite(canal1_pwm, pwm);
    ledcWrite(canal2_pwm, pwm);
  }

  /* Calculo RPM Motor A */
  if (revolucionA_flag){
    revolucionA_flag = false;    
    revolucionA_time = (micros() - last_timeA)*RT;
    rpm_motorA = (1/revolucionA_time)*60000000;    /* Un minuto son 60000000 ms */
    last_timeA = micros();        
  }
  
  /* Calculo RPM Motor B */
  if (revolucionB_flag){
    revolucionB_flag = false;    
    revolucionB_time = (micros() - last_timeB)*RT;
    rpm_motorB = (1/revolucionB_time)*60000000;    /* Un minuto son 60000000 ms */
    last_timeB = micros();        
  }
  
  /* Envío de datos */
  if (muestreo_flag) {
    muestreo_flag = false;
    Serial.print(millis());
    Serial.print(',');
    Serial.print(pwm);
    Serial.print(',');
    Serial.print(revolucionA_time);
    Serial.print(',');
    Serial.print(rpm_motorA);
    Serial.print(',');
    Serial.print(revolucionB_time);
    Serial.print(',');
    Serial.println(rpm_motorB);    
  }
}
