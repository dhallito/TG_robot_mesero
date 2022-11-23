#include "seguimiento_linea.h"

void iniciar_IR(){
  /* Iniciar Pines IR */
  for (int i = 0; i < 6; i++) {
    pinMode(adelanteIR_pin[i], INPUT);
    delay(10);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(atrasIR_pin[i], INPUT);
    delay(10);
  }
}

void leer_IR(){
  for (int i = 0; i < 6; i++) {
    adelanteIR_value[i] = digitalRead(adelanteIR_pin[i]);
  }
  for (int i = 0; i < 2; i++) {
    atrasIR_value[i] = digitalRead(atrasIR_pin[i]);
  }
}
