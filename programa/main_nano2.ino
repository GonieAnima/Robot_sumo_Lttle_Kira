//Definicion del PIN
#define SENSOR_LINEA 2
#define TD 12 //Traspaso de datos al arduino principal

void setup() {
  // Set up del sensor
pinMode(SENSOR_LINEA,INPUT);
pinMode(TD,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int linea = digitalRead(SENSOR_LINEA);
Serial.println(linea);
digitalWrite(TD,linea);
}
