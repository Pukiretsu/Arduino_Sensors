void setup() {
  // put your setup code here, to run once:
  String BTdata = "";
  char BTresponse;
  Serial.begin(9600);
  while(1)
  {
    Serial.end();
    delay(1000);
    Serial.begin(9600);
    Serial.println("Iniciando servicio bluetooth...");
    Serial.println('t');
    delay(2000);
    if(Serial.available()) // Si existe algo en el buffer inicia la operacion
    {
      Serial.println("Ok...");

      // Inicio de ciclo de recepcion de datos
      while(Serial.available())
      {
        char RCdataChar = Serial.read();
        
        if(RCdataChar != '\n')
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
