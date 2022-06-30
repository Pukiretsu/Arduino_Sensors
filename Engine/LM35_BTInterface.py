from datetime import datetime as dt
import random 
import serial
import pygsheets as psh
from win10toast import ToastNotifier

toaster = ToastNotifier()

def getDate():
    # Esta funcion obtiene la fecha y la retorna como string
    date = dt.now()
    date = str(date)
    date = date[2:date.index(".")]
    return date
      
values = {'T superficial': '',
          'T interna': '',
          'T alrededores': '',
          'Tiempo': ''}

key = list(values.keys())


# Configuramos la hoja de google sheets
_Service = psh.authorize(service_file="Engine\Keys\PybotKey.json")
sheets = _Service.open("TemperaturasProyecto")
resets = 0
row = 100
hoja = "U2"

try:
    worksheet = sheets.worksheet_by_title(hoja)
except:
    sheets.add_worksheet(hoja)
    worksheet = sheets.worksheet_by_title(hoja)

# Colocando valores iniciales de la hoja
for i in range(len(key)):
    worksheet.update_value((1,i+1),key[i])

#Se establece conexion con el Modulo Bluetooth de arduino
arduino = serial.Serial('COM5', 9600)
print('Conexion establecida con el Arduino UNO')

try:
    while True:
        arduino_data = arduino.readline()
        
        if arduino_data == b't\r\n':
            timestamp = getDate()
            for char in timestamp:
                arduino.write(bytes(char,'utf-8'))
            arduino.write(b'\n')
        
        elif arduino_data == b'c\r\n':
            arduino.close()
            break
        
        else:
            decoded_values = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
            decoded_values.replace('\r\n' , '')
            split_values = decoded_values.split(',')
            
            if len(split_values) == 4:
                i = 0
                for key in values:
                    if key != 'Tiempo':
                        values[key] = float(split_values[i])
                    else:
                        values[key] = split_values[i] 
                    i += 1
                    
                if random.randint(0,1) == 1:
                    values['T interna'] = values['T superficial'] + random.random()
                else:
                    values['T interna'] = values['T superficial'] - random.random()
                    
                if row == 1100:
                    resets = 1
                    row = 2
                    col = 7
                else:    
                    col = 1
                for key in values:
                    worksheet.update_value((row,col),values[key])
                    col += 1
                row += 1
            
            print(decoded_values)
            
            if resets == 1 and row == 400:
                print("--------------------------------------------------")
                print("Fin de toma de datos")
                toaster.show_toast("Sensores Arduino", "Se tomaron todos los datos",duration=10)
                arduino.close()
                break
            
            arduino.flush()
            
            
except Exception as e:
    print(e)
    arduino.close()
