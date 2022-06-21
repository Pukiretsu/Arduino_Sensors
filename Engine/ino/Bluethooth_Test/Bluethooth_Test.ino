long intData;
String BTdata = "";

void setup()  
{
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available())
  {
    long RCdataChar = Serial.read();
    if(isDigit(RCdataChar))
    {
      BTdata += (char)RCdataChar;
    }
    if(RCdataChar=='\n')
    {
      intData = BTdata.toInt();
      Serial.print("Dato recibido: ");
      Serial.println(intData);
      Serial.print("String recibido: ");
      Serial.println(BTdata);
      Serial.flush();
      BTdata = "";
    }
  }
}
