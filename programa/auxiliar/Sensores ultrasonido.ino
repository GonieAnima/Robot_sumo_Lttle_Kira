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

void loop(){
  sensores();
}
//Creamos el loop de detección
void sensores(){
  digitalWrite(TriggerD,LOW);
  delay(2);
  digitalWrite(TriggerD,HIGH);
  delay(10);
  digitalWrite(TriggerD,LOW);
  tD=pulseIn(EchoD,HIGH);  
 
  digitalWrite(TriggerI,LOW);
  delay(2);
  digitalWrite(TriggerI,HIGH);
  delay(10);
  digitalWrite(TriggerI,LOW);
  tI=pulseIn(EchoI,HIGH);
  //Estas dos lineas se pueden combinar

  distanciaD = (tD*.0343)/2;  
  distanciaI = (tI*.0343)/2;  

  serial.println("distancia derecha"+string(distanciaD)+"cm");
  serial.println("distancia izquierda"+string(distanciaI)+"cm");
}
  

