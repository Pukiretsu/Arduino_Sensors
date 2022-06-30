//Arduino Code - Humedad del suelo
 
int PinSeñal = A0; //Definimos el pin para el arduino
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  int humedad = analogRead(PinSeñal);
  Serial.print("Nivel de humedad del suelo: ");
  Serial.println(Humedad);
  delay(1000);
}
