#ifndef _MOTOR_H 
#define _MOTOR_H

#include <Arduino.h>
#include "variables.h"

void iniciar_motores();

void adelante_motorA();

void atras_motorA();

void detener_motorA();

void controlar_motorA(int ck);


void adelante_motorB();

void atras_motorB();

void detener_motorB();

void controlar_motorB(int ck);

#endif
