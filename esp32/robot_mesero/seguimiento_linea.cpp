#include "seguimiento_linea.h"

void iniciar_IR(){
  /* Iniciar Pines IR */
  for (int i = 0; i < 6; i++) {
    pinMode(atrasIR_pin[i], INPUT);
    delay(10);
  }
}

void leer_IR(){
  /* Iniciar Pines IR */
  for (int i = 0; i < 6; i++) {
    atrasIR_value[i] = digitalRead(atrasIR_pin[i]);
  }
}
