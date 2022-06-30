// Importamos librerias necesarias

// Para el manejo de SD
#include <SPI.h>
#include <SD.h>


// Declaracion de Variables Globales
String date;
File dataFile;
float _Temp[3]; // Para almacenar la temperatura de los sensores
String filename;
 
String getData() 
{
  // Funcion que obtiene el dato de la fecha desde una comunicación bluetooth
  String BTdata = "";
  // Reiniciamos los puertos de serial
  Serial.end();
  delay(1000);
  Serial.begin(9600);
  while(1)
  {
    Serial.println('t');
    delay(1000);
    if(Serial.available()) // Si existe algo en el buffer inicia la operacion
    {
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
  Serial.println("Iniciando servicio bluetooth...");
  date = getData();
  Serial.println("Ok...");
  
  //Creacion del archivo en la SD
  Serial.print("Iniciando archivo de datos en la SD...");
  filename = date.substring(0,8) + ".csv";
  // Comprobamos que el archivo exista y sea valido
  if(SD.exists(filename))
  {
    Serial.println("Ok...");
    Serial.println("CSV ya configurado...");
  }
  else
  {
    dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile)
    {
      // Se configura el archivo CSV en caso de no estar creado y se ubican los encabezados
      Serial.println("Ok...");
      Serial.print("Configurando CSV...");
      dataFile.println("T_s,T_in,T_amb,TimeStamp");
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
  date = getData();
  filename = date.substring(0,8) + ".csv";
  dataFile = SD.open(filename, FILE_WRITE);
  // Leemos la temperatura
  for (int i = 0; i < 3; i++)
  {
    // Leemos la temperatura
    _Temp[i] = analogRead(i);
    
    // Calculamos la temperatura
    _Temp[i] = (1.1 * _Temp[i] * 100.0)/1024.0;

    // Se envia el dato al puerto serial
    Serial.print(_Temp[i]);
    Serial.print(",");
    
    // Se transcribe el dato a la SD
    if (dataFile)
    {
      dataFile.print(_Temp[i]);
      dataFile.print(",");
    }
  }
  // Se pone el timeStamp
  Serial.print(date.substring(9,17));
  Serial.print("\n");
  dataFile.println(date.substring(9,17));
  dataFile.close();

  // Esperamos un tiempo para repetir el loop
  delay(3000);
}
