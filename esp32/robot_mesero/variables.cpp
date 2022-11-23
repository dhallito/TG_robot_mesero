#include "variables.h"

/* ----PINES---- */
/* Pines Motor A */
extern int enableA_pin = 12;
extern int input1_pin = 14;
extern int input2_pin = 27;
extern int encoderA = 13;

/* Pines Motor B */
extern int enableB_pin = 25;
extern int input3_pin = 32;
extern int input4_pin = 33;
extern int encoderB = 26;

/* Pines IR */
//extern int atrasIR_pin[6] = {16, 17, 35, 34, 39, 36};
extern int adelanteIR_pin[6] = {36, 39, 34, 35, 17, 16};
extern int atrasIR_pin[2] = {4, 0};

/* Pines Ultrasonido */
extern int outputUS_pin = 15;
extern int inputUS_pin = 2;

/* Pines Lector RFID */
extern int SS_PIN  = 5; 
extern int RST_PIN = 22;

/* ----VARIABLES MUESTREO---- */
extern int T = 100;    /* Periodo de muestreo en milisegundos */
extern int RT = 70;    /* Relación de transmisión */
extern float R = 0.05;   /* Radio rueda en m */
extern float L = 0.41;   /* Separacion de ruedas en m */
extern bool controlando = true;

extern unsigned long last_timeA = 0;   /*Ultimo tiempo de motor */
extern float revolucionA_time = 0;
extern float rpm_motorA = 0;
extern float rads_motorA = 0;
extern float setpoint_rpm_motorA = 0;
extern float ek_motorA[5] = {0, 0, 0, 0, 0};
extern float ck_motorA[5] = {0, 0, 0, 0, 0};
extern float ki_motorA = 1;
extern float kp_motorA = 3;

extern unsigned long last_timeB = 0;   /*Ultimo tiempo de motor */
extern float revolucionB_time = 0;
extern float rpm_motorB = 0;
extern float rads_motorB = 0;
extern float setpoint_rpm_motorB = 0;
extern float ek_motorB[5] = {0, 0, 0, 0, 0};
extern float ck_motorB[5] = {0, 0, 0, 0, 0};
extern float ki_motorB = 1;
extern float kp_motorB = 3;

/* ----VARIABLES PWM---- */
extern int F_pwm = 16000;    /* Frecuencia de PWM (Selección final = 16kHz */
extern int pwm = 5;    /* Valor PWM */
extern int canal1_pwm = 0;   /* Canal de PWM */
extern int canal2_pwm = 1;   /* Canal de PWM */
extern int resolucion = 8;   /* Resolución de 8 bits */
extern int change = 25;

/* ----VARIABLES ANGULO Y DISTANCIA---- */
extern float angulo_absoluto = 0;
extern float angulo_relativo = 0;
extern float angulo_giro = 0;
extern float distancia_ruedaA = 0;
extern float distancia_ruedaB = 0;
extern float distancia_relativa = 0;
extern float distancia_objetivo = 0.25;

/* ----VARIABLES SEGUIMIENTO LINEA---- */
extern bool adelanteIR_value[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
extern bool atrasIR_value[2] = {LOW, LOW};
extern float error_linea = 0;
extern float error_integral_linea = 0;
extern float correccion_linea = 0;
extern float ki_linea = 0.005;
extern float kp_linea = 2;
extern float velocidad_base = 30;
extern float last_time_linea = 0;
extern float distancia_minima = 0;

/* Variables de Estado */
extern int state=inicio;
extern bool iniciando_robot = false;
extern bool nueva_ruta = false;
extern bool nuevo_nodo = false;
extern bool angulo_alcanzado = false;
extern bool preparado = false;
extern bool objetivo_alcanzado = false;
extern char ruta[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
extern int ruta_size = 0;
extern int contador_ruta = 1;
extern char nodo_siguiente = ' ';
extern char nodo_actual = ' ';
extern float nodo_actual_angulos[9] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
extern String nodo_actual_id = "";
extern float nodo_siguiente_angulos[9] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
extern float nodo_siguiente_distancias[9] = {100, 100, 100, 100, 100, 100, 100, 100, 100};
extern String nodo_siguiente_id = "";

/* ----VARIABLES WIFI---- */
extern const char* ssid = "David_TG";
extern const char* password =  "david_tg";
