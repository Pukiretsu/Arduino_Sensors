void setup() {
  // put your setup code here, to run once:
  String BTdata = "";
  char BTresponse;
  while(1)
  {
    Serial.print("Iniciando servicio bluetooth...");
    Serial.print("s");
    BTresponse = Serial.read();
    if(Serial.available() && BTresponse == 's') // Si existe algo en el buffer inicia la operacion
    {
      Serial.println("Ok...");
      Serial.println("t");
      // Inicio de ciclo de recepcion de datos
      while(Serial.available())
      {
        char RCdataChar = Serial.read();
        if(RCdataChar!='\n')
        {
          BTdata += RCdataChar;
        }
        else
        {
          // Limpieza tras obtencion de datos.
          Serial.print("Exitoso, dato recibido: ");
          Serial.println(BTdata);
          Serial.flush();
        }
      }
      Serial.println("c");
      break;
    }
    else
    {
      Serial.println("Error...Reintentando en 3 segundos");
      delay(3000);
    }  
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
