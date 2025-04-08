//BIBLIOTECAS
#include <Servo.h>
#include "VL53L0X.h"


//VARIABLES DE TIEMPO
int errorT = 30;            //Temporizador de margen de error para botones
int debounceT = 200;        //Temporizador de debouncing
int raveT = 30;             //Temporizador de rave mientras se mantiene el boton pulsado RAVE RAVE Tsk Tsk Tsk ...
int startT=3000;            //Tiempo de inicio como dictaminado en las reglas
int giroT=0;                //Tiempo de giro en maniobras
int giro180t=1000;           //Tiempo para girar 180º

//VARIABLES DE SENSORES LASER
bool sdi = 0;
bool sdd = 0;
bool sai = 0;
bool sad = 0;

//INDICADORES
int pinLed = 13;


//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 9;                 // Motor Output Izquierdo A
int pinMOIB = 8;                 // Motor Output Izquierdo B
int pinMODA = 12;                // Motor Output Derecha A
int pinMODB = 10;                // Motor Output Derecha B

//SETUP DE VARIABLES DE SENSORES
VL53L0X sensor[6];  
const int xshut_pins[6] = {2, 3, 4, 5, 6, 7};  
const int UMBRAL = 1000;  // Distancia en mm para considerar detección           


//SETUP
void setup(){
  //INTERRUPCIONES (CODIGO PARA "COMUNICACIÓN" CON EL SEGUNDO ARDUINO)
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptInstance, RISING);

  //SERIAL MONITOR
  Serial.begin(115200);                 //Comenzar una conexión serial con el USB

  //SETUP DE SALIDAS Y ACTUADORES
  pinMode(pinMOIA, OUTPUT);  // Configura los pines como salidas
  pinMode(pinMOIB, OUTPUT);  
  pinMode(pinMODA, OUTPUT); 
  pinMode(pinMODB, OUTPUT); 

  //SETUP DE SENSORES
  pinMode(pinSDI, INPUT);  
  pinMode(pinSDD, INPUT); 
  pinMode(pinSAI, INPUT); 
  pinMode(pinSAD, INPUT);  
  pinMode(pinSI, INPUT); 

  //SENSORES LASER
  Serial.begin(115200);
  Wire.begin();
  
  for (int i = 0; i < 4; i++) pinMode(xshut_pins[i], OUTPUT), digitalWrite(xshut_pins[i], LOW);

  for (int i = 0; i < 4; i++) {
    delay(10);
    digitalWrite(xshut_pins[i], HIGH);
    delay(10);
    sensor[i].setAddress(0x30 + i);
    sensor[i].init();
    sensor[i].startContinuous();
  }

  delay(3000);             //Delay normativo de inicio
  combat();
}

void loop(){
  
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################




//COMBATE
void combat(){
  while(1==1){
    adelante();
    delay(1000);
    paro();
    delay(10000);
  }
}

//SENSORES LASER
void sensores(){
for (int i = 0; i < 6; i++) {
    bool detecta = sensor[i].readRangeContinuousMillimeters() < UMBRAL;
    Serial.print(detecta ? "1\t" : "0\t");  
  }
  Serial.println();
  delay(100);}

// COMBATE MICRO
void adelante(){DD();ID();}                               //Adelante

void paro(){IS();DS();}                                   //paro

void giroDerecha(){DA();ID();delay(giroT);}               //Giro Derecha

void giroIzquierda(){DD();IA();delay(giroT);}             //Giro Izquierda

void giro180(){DD();IA();delay(giro180t);}                 //Giro 180º

//SENTIDO DE GIRO RUEDAS
void DD(){                  //Rueda Derecha Delante
  digitalWrite(pinMODA,LOW);
  digitalWrite(pinMODB,HIGH);
}
void DA(){                  //Rueda Derecha Atras
  digitalWrite(pinMODB,LOW);
  digitalWrite(pinMODA,HIGH);
}
void ID(){                  //Rueda Izquierda Delante
  digitalWrite(pinMOIA,LOW);
  digitalWrite(pinMOIB,HIGH);
}
void IA(){                  //Rueda Izquierda Atras
  digitalWrite(pinMOIB,LOW);
  digitalWrite(pinMOIA,HIGH);
}
void DS(){                  //Rueda Derecha paro
  digitalWrite(pinMODB,LOW);
  digitalWrite(pinMODA,LOW);
}
void IS(){                  //Rueda Izquierda paro
  digitalWrite(pinMOIB,LOW);
  digitalWrite(pinMOIA,LOW);
}
void blink(){
  for(int x=0;x<200;x++){
  digitalWrite(13,HIGH);
  delay(250);
  digitalWrite(13,LOW);
  delay(250);
  }
}
