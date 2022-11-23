#ifndef _MAQUINA_ESTADOS_H 
#define _MAQUINA_ESTADOS_H

#include <Arduino.h>
#include "variables.h"
#include "seguimiento_linea.h"
#include "motor.h"
#include "lector_rfid.h"
#include "com_wifi.h"

int maquina_estados(int estado);

void calcular_nodo_actual();

float calcular_minimo_angulo(float angulo_siguiente);

int interpretar_nodo(char id_nodo);

#endif




/*#ifndef _MAQUINA_ESTADOS_H 
#define _MAQUINA_ESTADOS_H

#include <Arduino.h>
#include "com_serial.h"
#include "com_wifi.h"
#include "sensor_dht.h"
#include "variables.h"

class Maquina_Estados{
  private:
    int state;
  public:
    void maquina_estados(int estado);
    void set_state(int param);
    int get_state();
};

#endif*/
