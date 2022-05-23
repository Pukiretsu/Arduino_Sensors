from datetime import datetime
import serial
import time
import schedule
import csv

def saveCSV(data:dict, stamp:str) -> None:
    try:
        with open(f'Engine\data\\temperaturas_{stamp}.csv', 'x') as csv_file:
            fields = list(data.keys())
            
            writer = csv.DictWriter(csv_file,fields)
            
            writer.writeheader()
            writer.writerow(data)
    except:
        with open(f'Engine\data\\temperaturas_{stamp}.csv', 'a') as csv_file:
            fields = list(data.keys())
            
            writer = csv.DictWriter(csv_file,fields)
            writer.writerow(data)

def main_com():
    arduino = serial.Serial('COM3',9600)
    print('Conexion establecida con el Arduino UNO')
    arduino_data = arduino.readline()
    
    
    decoded_values = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    decoded_values.replace('\r\n','')
    list_values = decoded_values.split(',')

    actualtime = datetime.now()
    timestamp = actualtime.strftime("%H:%M:%S")
    
    n = 0
    for item in data:
        if n < len(list_values)-1:
            data[item] = (list_values[n])
            n += 1
        else:
            data[item] = timestamp
    
    
    print('----------------------------------------------------------------')
    print(f'-                          {timestamp}                            -')
    print('----------------------------------------------------------------')
                        
    print('\nDatos leidos desde el arduino:\n')
    for item in data:
        print(f'{item}:\t\t{data[item]}')
    
    print()
    try:
        saveCSV(data,mainstamp)
        print("Datos Almacenados con exito.")
    except Exception as e:
        print(f"No se pudo almacenar los datos... \n\tError: {e}")
    
    # Clean-up
    for item in data:
        data[item] = ''
    arduino.flush()
    arduino.close()
    list_values.clear() 
    print("\nConexion Terminada con exito.")
    print('----------------------------------------------------------------')

list_values = []
data = { 'Humedad (%)': '', 'Temp. (C)': '', 'Temp. (F)': '', 'Indice (C)': '', 'Indice (F)' : '', 'TimeStamp': ''}

actualtime = datetime.now()
mainstamp = actualtime.strftime("%d-%m-%Y_%H_%M_%S")

main_com()
schedule.every(2).minutes.do(main_com)

while True:
    schedule.run_pending()
    time.sleep(1)
