#include <Arduino.h>

/* Muestreo */
int T = 10;    /* Periodo de muestreo en milisegundos */
long echo1_time = 0;
long echo1_last = 0;

/* Pines Sensor 1 */
int trigger1_pin = 19;
int echo1_pin = 18;

/* Timer0: Muestreo */
bool muestreo_flag = false;
hw_timer_t * timer0 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer0(){   /* Funcion de interrupcion */
  muestreo_flag = true;
}

/* Timer3: Generar pulso ultrasonido */
bool ultrasonic_pulse_flag = false;
bool echo1_waiting = false;
hw_timer_t * timer3 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer3(){   /* Funcion de interrupcion */
  ultrasonic_pulse_flag = true;
}

/* GPIO Interrupcion echo 1 */
bool echo1_flag = false;
void IRAM_ATTR isr_echo1() {
  echo1_flag = true;
}

void setup() {
  Serial.begin(115200);

  /* Pines setup */
  pinMode(trigger1_pin, OUTPUT);
  pinMode(echo1_pin, INPUT);

  /* Timer 0 setup: Muestreo */
  timer0 = timerBegin(0, 80, true);    /*80MHz/80 = 1MHz -> 1 us */
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, T*1000, true);    /* Periodo de muestreo en us */
  timerAlarmEnable(timer0);

  /* Timer 3 setup: Muestreo */
  timer3 = timerBegin(3, 80, true);    /*80MHz/80 = 1MHz -> 1 us */
  timerAttachInterrupt(timer3, &onTimer3, true);
  timerAlarmWrite(timer3, 100000, true);    /* Periodo de muestreo en us */
  timerAlarmEnable(timer3);

  /* GPIO echo 1 Interrupt */
  attachInterrupt(echo1_pin, isr_echo1, FALLING);

  /* Inicio de datos */
  delay(2000);
  Serial.println("Iniciando");
}

void loop() {
  /* Calculo distancia Sensor Ultrasónico 1 */
  if (echo1_flag){
    echo1_flag = false;
    echo1_time = millis() - echo1_last;
    Serial.print(millis());
    Serial.print(",");
    Serial.print(echo1_last);
    Serial.print(",");
    Serial.println(echo1_time);
  }
  /* Pulso ultrasonico */
  if (ultrasonic_pulse_flag){
    ultrasonic_pulse_flag = false;
    digitalWrite(trigger1_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger1_pin, LOW);
    echo1_last = millis();
  }
  
  /* Envío de datos */
  if (muestreo_flag) {
    muestreo_flag = false;
  }
}
