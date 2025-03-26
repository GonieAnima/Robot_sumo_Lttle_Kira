//BIBLIOTECAS
#include <Servo.h>

//VARIABLES DE CALCULO Y AUXILIARES
int val=0;
int dump;

//VARIABLES DE TIEMPO
int errorT = 30;            //Temporizador de margen de error para botones
int debounceT = 200;        //Temporizador de debouncing
int raveT = 30;             //Temporizador de rave mientras se mantiene el boton pulsado RAVE RAVE Tsk Tsk Tsk ...
int startT=3000;            //Tiempo de inicio como dictaminado en las reglas
int giroT=0;                 //Tiempo de giro en maniobras
int giro180;                 //Tiempo para girar 180º

//BOTÓN
int pinBut = 10;            //Pin
int butState = 0;           //Estado del botón

//INDICADORES
int pinLed = 13;

//INTERRUPT     (COMUNICACIÓN CON EL SEGUNDO)
int interruptPin=2;           //Pin de interrupción

//PINS DE SENSORES
int pinSD = 11;                // PIN Sensor Derecho
int pinSI = 3;                 // PIN Sensor Izquierdo

//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 8;                 // Motor Output Izquierdo A
int pinMOIB = 9;                 // Motor Output Izquierdo B
int pinMODA = 10;                // Motor Output Derecha A
int pinMODB = 12;                // Motor Output Derecha B

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

  delay(3000)             //Delay normativo de inicio
}

void loop(){
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################

//INTERRUPCIONES DE COMUNICACIÓN    
void interruptInstance(){
  //QUE HACES CUANDO SE INTERRUMPE (PENDIENTE DE DEFINIR)
}

//COMBATE
void combat(){
  
}

// COMBATE MICRO
void adelante(){DD();ID();}                               //Adelante

void paro(){IS();DS();}                                   //paro

void giroDerecha(){DA();ID();delay(giroT);}               //Giro Derecha

void giroIzquierda(){DD();IA();delay(giroT);}             //Giro Izquierda

void giro180(){DD();IA();delay(giro180);}                 //Giro 180º

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