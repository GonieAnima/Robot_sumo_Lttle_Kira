//          DEBOUNCER DE BOTÓN (SI ES POSIBLE CON UN LM 555)
//          LED ENGANCHABLE CON RESISTENCIA ENGANCHADA (CON DISEÑO 3D DE SUJETADOR DE BOTÓN)
//          BOTÓN ALARGABLE

//BIBLIOTECAS
#include <Servo.h>

//VARIABLES DE CALCULO Y AUXILIARES
int val=0;
int dump;
int velocidad = 0;        // NO TENEMOS NI PUTA IDEA, HACER PRUEBAS

//VARIABLES DE TIEMPO
int errorT = 30;            //Temporizador de margen de error para botones
int blinkT = 500;           //Temporizador de parpadeo
int debounceT = 200;        //Temporizador de debouncing
int raveT = 30;             //Temporizador de rave mientras se mantiene el boton pulsado RAVE RAVE Tsk Tsk Tsk ...
int startT=3000;            //Tiempo de inicio como dictaminado en las reglas
int giroT=0;                 //Tiempo de giro en maniobras
int giro180;                 //Tiempo para girar 180º

//BOTÓN
int pinBut = 10;            //Pin
int butState = 0;           //Estado del botón

//Lectura de sensores
void sensor(){
int SD=digitalRead(pinSD);
int SI=digitalRead(pinSI);
}

//INDICADORES
int pinLed = 13;

//INTERRUPT     (COMUNICACIÓN CON EL SEGUNDO)
int interruptPin=2;

//Detección de sensores
int SD=digitalRead(pinSD);
int SI=digitalRead(pinSI);
int Detector=0    //Placeholder, cuando sepamos la salida de los sensores lo cambiamos

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
  pinMode(pinSD, INPUT);     //configura los pines como entradas
  pinMode(pinSI, INPUT); 
  //SETUP DE ENTRADAS Y SALIDAS PARA ENCENDIDO
  pinMode(pinBut,INPUT);
  pinMode(pinLed,OUTPUT);
  startup();             // DESMARCADO PARA PRUEBAS (TEMPORAL)
}

// LOOP PRINCIPAL DEL PROGRAMA
void loop(){
  testMotor();
}

//################################################### POR ABAJO TODO ESTO SON FUNCIONES #######################################################

//SECUENCIA DE INICIO 
void startup(){                     
  while(butState==0){                 //Mientras el boton no esté pulsado
    blink();                            //Función de parpadeo lento
    butState=digitalRead(pinBut);       //Revisa el boton por si ha cambiado
  }
  delay(debounceT);                     //Delay de debouncer 
  while(butState==1){                 //Mientras el botón esté pulsado
    blink_rave();                       //Led rave whoooo!
    butState=digitalRead(pinBut);       //Revisa el boton por si ha cambiado
  }
  delay(startT);                      //Delay de inicio
  combat();                           //MODO DE COMBATE
}


//INTERRUPCIONES DE COMUNICACIÓN    (FUNCIÓN HA DE SER OPTIMIZADA AL MILIMETRO)
  //Optimizada
void interruptInstance(){
  giro180();

}

  //No optimizada
//void interruptInstance(){
//  Serial.println("Interrupt!")
//}

//COMBATE

void combat(){
  adelante();
  
}

}
// COMBATE MICRO
void giroDerecha(){    //Programa par girar derecha
  DA();
  ID();
  delay(giroT);
  adelante();
}

void giroIzquierda(){         // for(X=0,X<=)
  DD();
  IA();
  delay(giroT);
  adelante();
}

void giro180(){                    //Programa para girar 180 grados
  DD();                            //Solo se activa por detección de línea
  IA();
  for (int X=0,X <= giro180,X=X+1){                                          //Mientras gira detecta para actuar acorde
    sensor();
    delay(1);
    if(SI == Detector){
      giroIzquierda();
   }
    else(SD== Detector){
      giroDerecha();
    }
  }
}
  


void adelante(){                       //Movimiento hacia adelante
  DD();
  ID();
  while (True){                        //Siempre que vaya hacia adelante detecta para actuar acorde
    sensor();
    if(SI == Detector){
      giroIzquierda();
    }
    else(SD== Detector){
      giroDerecha();
    }
  }
}       

void stop(){   //Las dos ruedas paran
  IS();
  DS();
  
}

// FUNCIONES DEL LED 
void blink(){                    //PARPADEO
  digitalWrite(pinLed,HIGH);        //Enciende led
  delay(blinkT);                    //Espera
  digitalWrite(pinLed,LOW);         //Apaga led
  delay(blinkT);                    //Espera
}

void blink_rave(){                //PARPADEO RAPIDO
  digitalWrite(pinLed,HIGH);        //Enciende led
  delay(raveT+errorT);              //Espera
  digitalWrite(pinLed,LOW);         //Apaga led
  delay(raveT);                     //Espera
}
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
void DS(){                  //Rueda Derecha Stop
  digitalWrite(pinMODB,LOW);
  digitalWrite(pinMODA,LOW);
}
void IS(){                  //Rueda Izquierda Stop
  digitalWrite(pinMOIB,LOW);
  digitalWrite(pinMOIA,LOW);
}

