//BIBLIOTECAS
#include <Servo.h>


//VARIABLES DE TIEMPO
int errorT = 30;            //Temporizador de margen de error para botones
int debounceT = 200;        //Temporizador de debouncing
int raveT = 30;             //Temporizador de rave mientras se mantiene el boton pulsado RAVE RAVE Tsk Tsk Tsk ...
int startT=3000;            //Tiempo de inicio como dictaminado en las reglas
int giroT=0;                //Tiempo de giro en maniobras
int giro180t=2000;           //Tiempo para girar 180º
int parot=200;

//INDICADORES
int pinLed = 13;

//INTERRUPT                          (COMUNICACIÓN CON EL SEGUNDO)
int interruptPin=2;                  //Pin de interrupción

//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 9;                 // Motor Output Izquierdo A
int pinMOIB = 8;                 // Motor Output Izquierdo B
int pinMODA = 12;                // Motor Output Derecha A
int pinMODB = 10;                // Motor Output Derecha B

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

  paro();
  delay(3000);             //Delay normativo de inicio
  combat();
}

void loop(){
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################

//INTERRUPCIONES DE COMUNICACIÓN    
void interruptInstance(){
  Serial.print("interrupt");
  paro();
  giro180();
  Serial.print("Acabado");
}

//COMBATE
void combat(){
  while(1==1){
  
    adelante();
    delay(10000);
    
    
   
  }
}

// COMBATE MICRO
void adelante(){DD();ID();}                               //Adelante

void paro(){IS();DS();
delay(parot);}                                  //paro

void giroDerecha(){DA();ID();delay(giroT);}               //Giro Derecha

void giroIzquierda(){DD();IA();delay(giroT);}             //Giro Izquierda

void giro180(){DD();IA();
for(int y=0;y<1000;y++){
  for(int b=0;b<100;b++){
    for(int n=0;n<10;n++){}
  }
}}                 //Giro 180º

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
