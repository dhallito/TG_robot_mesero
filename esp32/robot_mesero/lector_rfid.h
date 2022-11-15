#ifndef _LECTOR_RFID_H 
#define _LECTOR_RFID_H

#include <Arduino.h>
#include "variables.h"

#include <SPI.h>
#include <MFRC522.h>

void iniciar_rfid();

bool get_new_id();

#endif
