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

//INDICADORES
int pinLed = 13;

//INTERRUPT     (COMUNICACIÓN CON EL SEGUNDO)
int interruptPin=2;

//DETECCIÓN DE SENSORES
int ultraTime_F;
int ultraTime_I;
int ultraTime_D;

//PINS DE SENSORES
int pinSFU = 11;                // PIN Sensor Frontal Ultrasonido
int pinSFL = 3;                 // PIN Sensor Frontal Laser
int pinSIU = 4;                 // PIN Sensor Izquierdo Ultrasonido 
int pinSIL = 5;                 // PIN Sensor Izquierdo Laser
int pinSDU = 6;                 // PIN Sensor Derecho Ultrasonido
int pinSDL = 7;                 // PIN Sensor Derecho Laser

//SETUP DE VARIABLES DE ACTUADORES
int pinMOIA = 8;                 // Motor Output Izquierdo A
int pinMOIB = 9;                 // Motor Output Izquierdo B
int pinMODA = 10;                // Motor Output Derecha A
int pinMODB = 12;                // Motor Output Derecha B

Servo Izquierda;                // Define un servo llamado Izquierda
Servo Derecha;                  // Define un servo llamado Derecha

//SETUP
void setup(){
  //INTERRUPCIONES (CODIGO PARA "COMUNICACIÓN" CON EL SEGUNDO ARDUINO)
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptInstance, RISING);

  //SERIAL MONITOR
  Serial.begin(115200);                 //Comenzar una conexión serial con el USB

  //SETUP DE SALIDAS Y ACTUADORES
  Izquierda.attach(pinMOI);             // Engancha Izquierda a pinMOI
  Derecha.attach(pinMOD);               // Engancha Derecha a pinMOD
  Izquierda.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
  Derecha.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.

  //SETUP DE ENTRADAS Y SALIDAS PARA ENCENDIDO
  pinMode(pinBut,INPUT);
  pinMode(pinLed,OUTPUT);
  //startup();             // DESMARCADO PARA PRUEBAS (TEMPORAL)
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

// TEST DE VELOCIDAD DEL MOTOR
void testMotor(){                //TEST DE EL MOTOR CON ORDENADOR (PUEDE O NO SER ELIMINADO MAS TARDE)
  dump=Serial.parseInt();           //Set de preguntas para el usuario
  while(Serial.available()==0){     //Mientras el monitor serial no recibe nada
    val=Serial.parseInt();          //Busca un numero entero
  }
  Serial.println(val);              //Imprime el valor recibido para confirmar
  Izquierda.write(val);             //Usa el valor en el motor
}

//INTERRUPCIONES DE COMUNICACIÓN    (FUNCIÓN HA DE SER OPTIMIZADA AL MILIMETRO)
  //Optimizada
void interruptInstance(){

}

  //No optimizada
//void interruptInstance(){
//  Serial.println("Interrupt!")
//}

//COMBATE

void combat(){
  
}

}
// COMBATE MICRO
void giroDerecha(){
  DA;
  ID;
  delay(giroT);
}

void giroIzquierda(){
  DD;
  IA;
  delay(giroT);
}

void giro180(){
  DD;
  IA;
  delay(giro180);
}

void adelante(){

}       

void busca(){

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

