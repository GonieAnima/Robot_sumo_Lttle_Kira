//BIBLIOTECAS
#include "VL53L0X.h"
#include <Wire.h>

//VARIABLES DE TIEMPO
int errorT = 30;            //Temporizador de margen de error para botones
int debounceT = 200;        //Temporizador de debouncing
int raveT = 30;             //Temporizador de rave mientras se mantiene el boton pulsado RAVE RAVE Tsk Tsk Tsk ...
int startT=3000;            //Tiempo de inicio como dictaminado en las reglas
int giroT=0;                //Tiempo de giro en maniobras
int giro180t=1000;           //Tiempo para girar 180º
int am =90;           //potencia motores

//VARIABLE SENSOR LINEA
int linea = 0;
//Definicion del PIN
#define SENSOR_LINEA 2

//INDICADORES
int pinLed = 13;

//VARIABLES DE SENSORES LASER
int sl[3];
bool sdf = 0;            //sensor delantero frente
bool sdd = 0;            //sensor delantero derecho
bool sdi = 0;            //sensor delantero izquierdo
//7Frente 8Derecho 12Izquierdo

//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 6;                 // Motor Output Izquierdo A
int pinMOIB = 5;                 // Motor Output Izquierdo B
int pinMODA = 10;                // Motor Output Derecha A
int pinMODB = 11;                // Motor Output Derecha B


//SETUP DE VARIABLES DE SENSORES LASER
VL53L0X sensor[3];  
const int xshut_pins[3] = {7, 8, 12};  //Pines de sensore laser ,Vicente:HAZ PRUEBAS CON ESTO PORFIS 
const int UMBRAL = 150;  // Distancia en mm para considerar detección           


//SETUP
void setup(){

  //SERIAL MONITOR
  Serial.begin(115200);                 //Comenzar una conexión serial con el USB

  //SETUP DE SALIDAS Y ACTUADORES
  pinMode(pinMOIA, OUTPUT);  // Configura los pines como salidas
  pinMode(pinMOIB, OUTPUT);  
  pinMode(pinMODA, OUTPUT); 
  pinMode(pinMODB, OUTPUT); 

  //SETUP DE SENSOR LINEA
  pinMode(SENSOR_LINEA,INPUT); //int linea = digitalRead(SENSOR_LINEA);  copiar y pegar cada vez que queramos detectar
 
//SENSORES LASER
  Wire.begin();
  
  for (int i = 0; i < 3; i++) pinMode(xshut_pins[i], OUTPUT), digitalWrite(xshut_pins[i], LOW);

  for (int i = 0; i < 3; i++) {
    delay(10);
    digitalWrite(xshut_pins[i], HIGH);
    delay(10);
    sensor[i].setAddress(0x30 + i);
    sensor[i].init();
    sensor[i].startContinuous();
  }
       
  paro();
  delay(3000);             //Delay normativo de inicio
}

void combate(){
  




void loop(){
 while(1==1){ 
  adelante();
  sensores();
  if(linea==0){
    atras();
    delay(350);
    giro180();
    delay(400);
    }
  }
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################
//SENSORES
void sensores(){

  linea = digitalRead(SENSOR_LINEA);
  for (int i = 0; i < 3; i++) {
    bool detecta = sensor[i].readRangeContinuousMillimeters() < UMBRAL;
    Serial.print(detecta ? "1\t" : "0\t");  
    sl[i]=detecta;
  }

  sdf = sl[0];
  sdd = sl[1];
  sdi = sl[2];

  Serial.println();
  delay(10);
}

// COMBATE MICRO
void adelante(){DD();ID();}                               //Adelante

void paro(){IS();DS();}                                   //paro

void giroDerecha(){DA();ID();delay(giroT);}               //Giro Derecha

void giroIzquierda(){DD();IA();delay(giroT);}             //Giro Izquierda

void giro180(){DD();IA();}                 //Giro 180º

void atras(){ 
  analogWrite(pinMOIB,0);
  analogWrite(pinMOIA,200);
  analogWrite(pinMODB,0);
  analogWrite(pinMODA,200);
}

//SENTIDO DE GIRO RUEDAS
void DD(){                  //Rueda Derecha Delante
  analogWrite(pinMODA,0);
  analogWrite(pinMODB,am);
}
void DA(){                  //Rueda Derecha Atras
  analogWrite(pinMODB,0);
  analogWrite(pinMODA,am);
}
void ID(){                  //Rueda Izquierda Delante
  analogWrite(pinMOIA,0);
  analogWrite(pinMOIB,am);
}
void IA(){                  //Rueda Izquierda Atras
  analogWrite(pinMOIB,0);
  analogWrite(pinMOIA,am);
}
void DS(){                  //Rueda Derecha paro
  analogWrite(pinMODB,0);
  analogWrite(pinMODA,0);
}
void IS(){                  //Rueda Izquierda paro
  analogWrite(pinMOIB,0);
  analogWrite(pinMOIA,0);
}
void blink(){
  for(int x=0;x<200;x++){
  digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
  }
}
