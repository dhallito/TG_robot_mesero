#include "maquina_estados.h"

int last_time_prueba = 0;

int maquina_estados(int estado){
  //Serial.println(estado);
  switch (estado) {
    case inicio:
      setup_server();
      iniciar_IR();
      iniciar_motores();
      iniciar_rfid();
      state = operacion;
      break;
    case operacion:
      if (iniciando_robot){
        detener_motorA();
        detener_motorB();
        delay(3000);
        iniciando_robot = false;   
      }
      if (nueva_ruta) {
        state = calcular_nodo;
      }else if (nuevo_nodo){
        state = alcanzar_angulo; 
      }else if (angulo_alcanzado){
        state = avanzar;
      }else if (preparado){
        state = seguir_linea;
      }else{
        state = operacion;
      }
      break;
    case calcular_nodo:
      if (contador_ruta < ruta_size){
        nodo_siguiente = ruta[contador_ruta];
        calcular_nodo_actual();
        angulo_giro = calcular_minimo_angulo(nodo_siguiente_angulos[interpretar_nodo(nodo_siguiente)]);
        distancia_minima = nodo_siguiente_distancias[interpretar_nodo(nodo_siguiente)];
        nuevo_nodo = true;
        nueva_ruta = false;
        if (angulo_giro > 0){
          adelante_motorB();
          atras_motorA();
        }else if (angulo_giro < 0){
          atras_motorB();
          adelante_motorA();
        }else{
          nuevo_nodo = false;
          preparado = true;
          angulo_absoluto = nodo_siguiente_angulos[interpretar_nodo(nodo_siguiente)];
          angulo_relativo = 0;
          distancia_ruedaA = 0;
          distancia_ruedaB = 0;
          detener_motorA();
          detener_motorB();
          adelante_motorA();
          adelante_motorB();
        }
        setpoint_rpm_motorA = 40;
        setpoint_rpm_motorB = 40;
      }else{
        nueva_ruta = false;
        contador_ruta = 1;
      }
      state = operacion;
      break;
    case alcanzar_angulo:
      if (angulo_giro > 0){
        angulo_relativo = (distancia_ruedaB + distancia_ruedaA)/L;
      }else if (angulo_giro < 0){    
        angulo_relativo = -(distancia_ruedaB + distancia_ruedaA)/L;
      }
      if (abs(angulo_relativo - angulo_giro) < 0.02){
        nuevo_nodo = false;
        preparado = true;
        angulo_absoluto = nodo_siguiente_angulos[interpretar_nodo(nodo_siguiente)];
        angulo_relativo = 0;
        distancia_ruedaA = 0;
        distancia_ruedaB = 0;
        detener_motorA();
        detener_motorB();
        adelante_motorA();
        adelante_motorB();
        delay(1000);
      }
      state = operacion;
      break;
    case avanzar:
      distancia_relativa = (distancia_ruedaB + distancia_ruedaA)/2;
      if (abs(distancia_relativa - distancia_objetivo) < 0.001){
        angulo_alcanzado = false;
        preparado = true;
        distancia_relativa = 0;
        distancia_ruedaA = 0;
        distancia_ruedaB = 0;
        detener_motorA();
        detener_motorB();
        adelante_motorA();
        adelante_motorB();
      }
      state = operacion;
      break;
    case seguir_linea:
      if (millis() - last_time_linea > 100){
        last_time_linea = millis();
        distancia_relativa = (distancia_ruedaB + distancia_ruedaA)/2;
        if (distancia_relativa < distancia_minima*0.9){
          leer_IR();
          if (adelanteIR_value[2] or adelanteIR_value[3]){
            adelanteIR_value[5]=LOW;
            adelanteIR_value[0]=LOW;
          }
          error_linea = -4*adelanteIR_value[0] - 3.5*adelanteIR_value[1] - 3*adelanteIR_value[2] - 0*atrasIR_value[1] + 0*atrasIR_value[0] + 3*adelanteIR_value[3] + 3.5*adelanteIR_value[4] + 4*adelanteIR_value[5];
          error_integral_linea = error_integral_linea + error_linea;
          correccion_linea = kp_linea*error_linea + ki_linea*error_integral_linea;
          setpoint_rpm_motorA = velocidad_base - correccion_linea;
          setpoint_rpm_motorB = velocidad_base + correccion_linea;
        }else{
          controlando = false;
          if(get_new_id()){
            preparado = false;
            nueva_ruta = true;
            contador_ruta += 1;
            nodo_actual = nodo_siguiente;
            distancia_ruedaA = 0;
            distancia_ruedaB = 0;
            detener_motorA();
            detener_motorB();
            controlando = true;
            Serial.println(nodo_actual);
          }
        }
      }      
//        for (int i = 0; i < 6; i++) {
//          Serial.print(atrasIR_value[i]);
//        }
//        Serial.println();
//        Serial.print(error_linea);
//        Serial.print(',');
//        Serial.print(setpoint_rpm_motorA);
//        Serial.print(',');
//        Serial.print(setpoint_rpm_motorB);
//        Serial.print(',');
//        Serial.print(rpm_motorA);
//        Serial.print(',');
//        Serial.print(rpm_motorB);
//        Serial.print(',');
//        Serial.println(correccion_linea);
      
      state = operacion;
      break;
  }
}

void calcular_nodo_actual(){
  for (int i = 0; i < 9; i++) {
    nodo_siguiente_angulos[i] = 0;
    nodo_siguiente_distancias[i] = 0;
  }
  
  switch(nodo_actual){
    case 'A':
      nodo_siguiente_angulos[2] = 1.57;
      nodo_siguiente_distancias[2] = 1.00;
      break;
    case 'B':
      nodo_siguiente_angulos[2] = 0;
      nodo_siguiente_angulos[4] = 1.57;

      nodo_siguiente_distancias[2] = 1;
      nodo_siguiente_distancias[4] = 1;
      break;
    case 'C':
      nodo_siguiente_angulos[0] = -1.57;
      nodo_siguiente_angulos[1] = 3.14;
      nodo_siguiente_angulos[3] = 0;
      nodo_siguiente_angulos[5] = 1.57;

      nodo_siguiente_distancias[0] = 1;
      nodo_siguiente_distancias[1] = 1;
      nodo_siguiente_distancias[3] = 1;
      nodo_siguiente_distancias[5] = 0.8;
      break;
    case 'D':
      nodo_siguiente_angulos[2] = 3.14;
      nodo_siguiente_angulos[6] = 1.57;

      nodo_siguiente_distancias[2] = 1;
      nodo_siguiente_distancias[6] = 1.20;
      break;
    case 'E':
      nodo_siguiente_angulos[1] = -1.57;
      nodo_siguiente_angulos[7] = 1.57;

      nodo_siguiente_distancias[1] = 1;
      nodo_siguiente_distancias[7] = 1;
      break;
    case 'F':
      nodo_siguiente_angulos[2] = -1.57;
      nodo_siguiente_angulos[8] = 1.57;

      nodo_siguiente_distancias[2] = 0.8;
      nodo_siguiente_distancias[8] = 1.20;
      break;
    case 'G':
      nodo_siguiente_angulos[3] = -1.57;
      nodo_siguiente_angulos[8] = 2.47;

      nodo_siguiente_distancias[3] = 1.2;
      nodo_siguiente_distancias[8] = 1.28;
      break;
    case 'H':
      nodo_siguiente_angulos[4] = -1.57;
      nodo_siguiente_angulos[8] = 0;
      
      nodo_siguiente_distancias[4] = 1;
      nodo_siguiente_distancias[8] = 1;
      break;
    case 'I':
      nodo_siguiente_angulos[5] = -1.57;
      nodo_siguiente_angulos[6] = -0.67;
      nodo_siguiente_angulos[7] = 3.14;

      nodo_siguiente_distancias[5] = 1.2;
      nodo_siguiente_distancias[6] = 1.28;
      nodo_siguiente_distancias[7] = 1;
      break;
  }
}

float calcular_minimo_angulo(float angulo_siguiente){
  if (angulo_siguiente-angulo_absoluto > 3.14){
    return (angulo_siguiente-angulo_absoluto)-6.28;
  }else if (angulo_siguiente-angulo_absoluto < -3.14){
    return 6.28 + (angulo_siguiente-angulo_absoluto);
  }else{
    return angulo_siguiente-angulo_absoluto;
  }       
}

int interpretar_nodo(char id_nodo){
  int nodo_value;
  switch(id_nodo){
    case 'A':
      nodo_value = 0;
      break;
    case 'B':
      nodo_value = 1;
      break;
    case 'C':
      nodo_value = 2;
      break;
    case 'D':
      nodo_value = 3;
      break;
    case 'E':
      nodo_value = 4;
      break;
    case 'F':
      nodo_value = 5;
      break;
    case 'G':
      nodo_value = 6;
      break;
    case 'H':
      nodo_value = 7;
      break;
    case 'I':
      nodo_value = 8;
      break;
  }
  return nodo_value;
}
