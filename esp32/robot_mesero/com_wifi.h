/*#ifndef _COM_WIFI_H_
#define _COM_WIFI_H_

#include <Arduino.h>
#include <WiFi.h>
#include "variables.h"

class Com_Wifi{
  private:
    //Variables
    const char* ssid = "Dhallito";
    const char* pass = "elwifi123";
    String header;
    //Funciones
    void wifi_interpretar(String header);
  public:
    //Variables
    //Funciones
    void wifi_setup();
    void wifi_request();
};

#endif*/
