#include <Arduino.h>

/* Muestreo */
int T = 10;    /* Periodo de muestreo en milisegundos */

/* Pines Sensor IR */
int ir1_pin = 12;
int ir2_pin = 14;

/* Timer0: Muestreo */
bool ir1_state;
bool ir2_state;
bool muestreo_flag = false;
hw_timer_t * timer0 = NULL;    /* Crear variable timer */
void IRAM_ATTR onTimer0(){   /* Funcion de interrupcion */
  muestreo_flag = true;
}

void setup() {
  Serial.begin(115200);

  /* Pines setup */
  pinMode(ir1_pin, INPUT_PULLUP);
  pinMode(ir2_pin, INPUT_PULLUP);

  /* Timer 0 setup: Muestreo */
  timer0 = timerBegin(0, 80, true);    /*80MHz/80 = 1MHz -> 1 us */
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, T*1000, true);    /* Periodo de muestreo en us */
  timerAlarmEnable(timer0);
  
  /* Inicio de datos */
  delay(1000);
  Serial.println("Iniciando");
}

void loop() {  
  /* Envío de datos */
  if (muestreo_flag) {
    muestreo_flag = false;
    bool ir1_state = digitalRead(ir1_pin);
    bool ir2_state = digitalRead(ir2_pin);
    Serial.print(millis());
    Serial.print(",");
    Serial.print(ir1_state);
    Serial.print(",");
    Serial.println(ir2_state);
  }
}
