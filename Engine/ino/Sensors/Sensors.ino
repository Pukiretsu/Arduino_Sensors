// Importamos librerias necesarias

// Para el manejo de SD
#include <SPI.h>
#include <SD.h>


// Declaracion de Variables Globales
String date;
File dataFile;
float _TempS1, _TempS2, _TempS3, _TempS4, _TempS5; // Para almacenar la temperatura de los sensores
// Ubicacion de sensores en cada pin

String getDataTime() 
{
  String BTdata = "";
  while(1)
  {
    Serial.print("Iniciando servicio bluetooth...");
    if(Serial.available()) // Si existe algo en el buffer inicia la operacion
    {
      Serial.println("Ok...");

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
          Serial.flush();
        }
      }
      break;
    }
    else
    {
      Serial.println("Error...Reintentando en 3 segundos");
      delay(3000);
    }  
  }
  return BTdata;
}

void setup() 
{
  // Configuraciones iniciales
  // Cambiamos referencia de las entradas analógicas
  analogReference(INTERNAL);
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);

  // Inicializacion de SD (Si no hay el programa no arranca)
  Serial.print("Iniciando Tarjeta SD...");
  if (!SD.begin(10)) 
  { 
    Serial.println("La tarjeta SD no se pudo inicializar...");
    while(!SD.begin(10))
    {
      delay(1000);
    }
  }
  Serial.println("Ok...");
  
  //Obteniendo la fecha y hora desde comunicacion BT
  date = getDataTime();
  //Creacion del archivo en la SD
  Serial.print("Iniciando archivo de datos en la SD...");
  String filename = date.substring(0,8) + ".csv";
  if(SD.exists(filename))
  {
    Serial.println("Ok...");
    Serial.println("CSV configurado...");
  }
  else
  {
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile)
    {
      Serial.println("Ok...");
      Serial.print("Configurando CSV...");
      dataFile.println("S1,S2,S3,S4,S5,TimeStamp");
      dataFile.close();
      Serial.print("Ok...");
    }
    else 
    {
      Serial.println("Error...");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
