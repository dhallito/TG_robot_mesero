/*#include "com_serial.h"

int Com_Serial::leer_serial(){
  int R = 1;
  while(Serial.available()>0){
    char c = Serial.read();
    if(c == '\n'){ // caracter de cambio de linea ==> termino palabra
      buff[index1] = '\0';
      R = interpretar();
      index1 = 0;
    }
    else{
      buff[index1] = c;
      index1++;
    }
  }
  return R;
}

int Com_Serial::interpretar(){
  int R = 1;
  if (strlen(buff) == 2) { // corroborar si la longitud de buff tiene los dos caracteres
    if (buff[0] == 'E') { // cambio de estado
      int val = atoi(buff + 1);
      if (val > 0 && val <= 6) {
        R = val;
      }  
    }
    else if (buff[0] == 'C') { // Activar controlador A1 // Desactivar A0
      int val = atoi(buff + 1);
      if (val == 0){
        Serial.println("Desactivando control automático de temperatura");
        control_automatico = false;
      }
      else if (val == 1){
        Serial.println("Activando control automático de temperatura");
        control_automatico = true;
      }
    }
  }
  else if (strlen(buff) == 6) { // Verificar si tiene los caracteres del setpoint de temperatura
    if (buff[0] == 'T') { // Verificar si inicia con el comando de setpoint de temperatura
      float val = atof(buff + 1);
      sp_temperatura = val;
      Serial.println("Nuevo set point: " + String(sp_temperatura) + "°C");
    }
  }
  
  return R;
  
}*/
  
