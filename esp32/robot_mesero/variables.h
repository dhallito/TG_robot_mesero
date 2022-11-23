#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <Arduino.h>

/* ----PINES---- */
/* Pines Motor A */
extern int enableA_pin;
extern int input1_pin;
extern int input2_pin;
extern int encoderA;

/* Pines Motor B */
extern int enableB_pin;
extern int input3_pin;
extern int input4_pin;
extern int encoderB;

/* Pines IR */
extern int adelanteIR_pin[6];
extern int atrasIR_pin[2];

/* Pines Ultrasonido */
extern int outputUS_pin;
extern int inputUS_pin;

/* Pines Lector RFID */
extern int SS_PIN; 
extern int RST_PIN;

/* ----VARIABLES MUESTREO---- */
extern int T;    /* Periodo de muestreo en milisegundos */
extern int RT;    /* Relación de transmisión */
extern float R;   /* Radio rueda en m */
extern float L;   /* Separacion de ruedas en m */
extern unsigned long last_timeA;   /*Ultimo tiempo de motor */
extern float revolucionA_time;
extern float rpm_motorA;
extern float rads_motorA;
extern float setpoint_rpm_motorA;
extern float ek_motorA[5];
extern float ck_motorA[5];
extern float ki_motorA;
extern float kp_motorA;
extern bool controlando;

extern unsigned long last_timeB;   /*Ultimo tiempo de motor */
extern float revolucionB_time;
extern float rpm_motorB;
extern float rads_motorB;
extern float setpoint_rpm_motorB;
extern float ek_motorB[5];
extern float ck_motorB[5];
extern float ki_motorB;
extern float kp_motorB;

/* ----VARIABLES PWM---- */
extern int F_pwm;    /* Frecuencia de PWM (Selección final = 16kHz */
extern int pwm;    /* Valor PWM */
extern int canal1_pwm;   /* Canal de PWM */
extern int canal2_pwm;   /* Canal de PWM */
extern int resolucion;   /* Resolución de 8 bits */
extern int change;

/* ----VARIABLES ANGULO Y DISTANCIA---- */
extern float angulo_absoluto;
extern float angulo_relativo;
extern float angulo_giro; 
extern float distancia_ruedaA;
extern float distancia_ruedaB;
extern float distancia_relativa;
extern float distancia_objetivo;


/* ----VARIABLES SEGUIMIENTO LINEA---- */
extern bool adelanteIR_value[6];
extern bool atrasIR_value[2];
extern float error_linea;
extern float error_integral_linea;
extern float correccion_linea;
extern float ki_linea;
extern float kp_linea;
extern float velocidad_base;
extern float last_time_linea;

/* ----VARIABLES ESTADO---- */
enum estado_global{inicio = 0, operacion = 1, alcanzar_angulo = 2, avanzar=3, seguir_linea = 4, calcular_nodo = 5};
extern int state;
extern bool iniciando_robot;
extern bool nueva_ruta;
extern bool nuevo_nodo;
extern bool angulo_alcanzado;
extern bool preparado;
extern bool objetivo_alcanzado;
extern char ruta[10];
extern int ruta_size;
extern int contador_ruta;
extern char nodo_siguiente;
extern char nodo_actual;
extern float nodo_actual_angulos[9];
extern String nodo_actual_id;
extern float nodo_siguiente_angulos[9];
extern float nodo_siguiente_distancias[9];
extern String nodo_siguiente_id;
extern float distancia_minima;

/* ----VARIABLES WIFI---- */
extern const char* ssid;
extern const char* password;

#endif
