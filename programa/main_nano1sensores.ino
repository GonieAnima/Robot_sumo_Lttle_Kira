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
int sl[4];
bool sdi = 0;            //sensor delantero izquierdo
bool sdd = 0;            // //sensor delantero derecho
bool sai = 0;             //sensor anterior izquierdo
bool sad = 0;             //sensor anterior derecho

//VARIABLE SENSOR LINEA
int linea = 0;
//Definicion del PIN
#define SENSOR_LINEA 2

//INDICADORES
int pinLed = 13;


//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 9;                 // Motor Output Izquierdo A
int pinMOIB = 8;                 // Motor Output Izquierdo B
int pinMODA = 12;                // Motor Output Derecha A
int pinMODB = 10;                // Motor Output Derecha B

//SETUP DE VARIABLES DE SENSORES LASER
VL53L0X sensor[4];  
const int xshut_pins[4] = {2, 3, 4, 5};  //Pines de sensore laser ,Vicente:HAZ PRUEBAS CON ESTO PORFIS 
const int UMBRAL = 1000;  // Distancia en mm para considerar detección           


//SETUP
void setup(){

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
  pinMode(SENSOR_LINEA,INPUT); //int linea = digitalRead(SENSOR_LINEA);  copiar y pegar cada vez que queramos detectar
  
  
 

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
  paro();
  delay(3000);             //Delay normativo de inicio
  combat();
}

void loop(){
  
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################




//COMBATE
void combat(){               //Cada sensor tiene un linea de acción y luego vuelve al bucle
  while(1==1){
    adelante();
    sensores();
    linea=digitalRead(SENSOR_LINEA);
    if (linea==1){giro180();}
    else if(sdd == 1){giroDerecha();}
    else if(sdi==1){giroIzquierda();}
    else if(sad==1){giro180();giroIzquierda();}
    else (sai==){giro180();giroDerecha();}
  }
}


//SENSORES LASER    //Funcion para detectar los sensores láser y crear unas variables manejables
void sensores(){
int sl[4];
for (int i = 0; i < 4; i++) {
    bool detecta = sensor[i].readRangeContinuousMillimeters() < UMBRAL;
    Serial.print(detecta ? "1\t" : "0\t");  
    int sl[i] = detecta ? "1\t" : "0\t";
    if (i==0){sdi= sl[i];}                            //No es lo más optimo pero, asigna una variable a los sensores con la que podemos trabajar
    else if(i==1){sdd=sl[i];}                          //o eso deberia hacer si no estoy Bobobó
    else if(i==2){sai=sl[i];}
    else(i==3){sad=sl[i];} }
  serial.print("sdd: ",sdd," sdi: ",sdi," sai: ",sai, " sad: ",sad);
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
