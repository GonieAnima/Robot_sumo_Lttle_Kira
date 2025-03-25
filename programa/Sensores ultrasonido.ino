//Sensores ultrasonido bucle de detección
int  TriggerD=7;
int EchoD=8;
int TriggerI=9;
int EchoI=10;
//variables
float tD =0;
float distanciaD =0;
float tI =0;
float distanciaI =0;

//Se define si los pines son de entrada o salida
void setup(){
  Serial.begin(9600);
  pinMode(TriggerD,OUTPUT);
  pinMode(EchoD,INPUT);
  pinMode(TriggerI,OUTPUT);
  pinMode(EchoI,INPUT);
}
//Creamos el loop de detección
void sensores(){
  digitalWrite(TriggerD,HIGH);
  delay(2);                           //Hace falta reisar los tiempos y su efectoe en el 
  digitalWrite(TriggerD,LOW);         //    combate
  delay(10);
  digitalWrite(TriggerD,HIGH);
  digitalWrite(TriggerI,HIGH);
  delay(2);
  digitalWrite(TriggerI,LOW);
  delay(10);
  digitalWrite(TriggerI,HIGH);

  tI=pulseIn(EchoI,HIGH);
  tD=pulseIn(EchoD,HIGH);    //Estas dos lineas se pueden combinar

  distanciaD =tD/58;
  distanciaI =tI/58
  
//
