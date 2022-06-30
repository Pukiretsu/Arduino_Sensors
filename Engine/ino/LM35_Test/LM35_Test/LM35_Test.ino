// Declaracion de variables globales
float Temp; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
 
void setup() {
  // Cambiamos referencia de las entradas analógicas
  analogReference(INTERNAL);
  
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
}
 
void loop() {

  // Leemos la temperatura
  Temp = analogRead(0);
    
  // Calculamos la temperatura
  Temp = (1.1 * Temp * 100.0)/1024.0;

  // Se envia el dato al puerto serial
  Serial.print("La temperatura es: ");
  Serial.print(Temp);
  Serial.println(" °C");
  // Esperamos un tiempo para repetir el loop
  delay(10000);
}
