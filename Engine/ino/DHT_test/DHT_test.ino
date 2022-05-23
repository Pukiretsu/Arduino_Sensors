#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

  float h = dht.readHumidity();

  float t = dht.readTemperature();
  
  float f = dht.readTemperature(true);
 
  // In case an read Error occurs
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("ERROR");
    return;
  }
 
  float hif = dht.computeHeatIndex(f, h);
  
  float hic = dht.computeHeatIndex(t, h, false);

  // Serial Port Communication
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(f);
  Serial.print(",");
  Serial.print(hic);
  Serial.print(",");
  Serial.print(hif);
  Serial.println(",");
  delay(5000);

}
