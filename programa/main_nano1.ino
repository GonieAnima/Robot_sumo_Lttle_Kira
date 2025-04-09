//BIBLIOTECAS
#include <Servo.h>


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


//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 6;                 // Motor Output Izquierdo A
int pinMOIB = 5;                 // Motor Output Izquierdo B
int pinMODA = 10;                // Motor Output Derecha A
int pinMODB = 11;                // Motor Output Derecha B
       
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
  pinMode(SENSOR_LINEA,INPUT); //int linea = digitalRead(SENSOR_LINEA);  copiar y pegar cada vez que queramos detectar
  
  
 

  //SENSORES LASER
  Serial.begin(115200);
  
  paro();
  delay(3000);             //Delay normativo de inicio
}

void loop(){
giro180();
delay(200);
 while(1==1){ 
 adelante();
  linea = digitalRead(SENSOR_LINEA);
  if(linea==0){
    atras();
    delay(350);
    giro180();
    delay(400);
    }}
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################


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
  analogWrite(pinMODA,200);}

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
