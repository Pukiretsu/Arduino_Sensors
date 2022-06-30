//Arduino Code - Humedad del suelo
 
int PinSensor = A0; //Definimos el pin para el arduino
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  int humedad = analogRead(PinSensor);
  Serial.print("Nivel de humedad del suelo: ");
  Serial.println(humedad);
  delay(1000);
}
