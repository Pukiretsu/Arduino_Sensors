// Importamos librerias necesarias

// Para el manejo de SD
#include <SPI.h>
#include <SD.h>


// Declaracion de Variables Globales
long ActualUNIXTime;
File dataFile;
float _TempS1, _TempS2, _TempS3, _TempS4, _TempS5; // Para almacenar la temperatura de los sensores
// Ubicacion de sensores en cada pin
int pinS1 = 0; 
int pinS2 = 1;
int pinS3 = 2;
int pinS4 = 3;
int pinS5 = 4;

void setup() {

  // Configuraciones iniciales
  // Cambiamos referencia de las entradas analógicas
  analogReference(INTERNAL);
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);

  // Inicializacion de SD (Si no hay el programa no arranca)
  Serial.println("Iniciando Tarjeta SD...");
  if (!SD.begin(10)) 
  { 
    Serial.println("La tarjeta SD no se pudo inicializar...");
    while(!SD.begin(10))
    {
      delay(1000);
    }
  }
  Serial.println("Conexion exitosa con la Tarjeta SD...");
  
  //Obteniendo la fecha y hora desde comunicacion BT
  getUNIXTime();
}

void getUNIXTime() 
{
  while(1)
  {
    Serial.print("Iniciando servicio bluetooth...");
    if(Serial.available()) // Si existe algo en el buffer inicia la operacion
    {
      Serial.println("Ok...");
      // Variables privadas para funcionamiento
      long UnixTime;
      String BTdata = "";

      // Inicio de ciclo de recepcion de datos
      while(Serial.available())
      {
        long RCdataChar = Serial.read();
        if(isDigit(RCdataChar))
        {
          BTdata += (char)RCdataChar;
        }
        if(RCdataChar=='\n')
        {
          UnixTime = BTdata.toInt();
          Serial.print("Tiempo UNIX: ");
          Serial.println(UnixTime);
          // Limpieza tras obtencion de datos.
          Serial.flush();
          BTdata = "";
          
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
  
    
  //return UnixTime;
}

void loop() {
  // put your main code here, to run repeatedly:

}
