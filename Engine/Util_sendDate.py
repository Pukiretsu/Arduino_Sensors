import calendar
import datetime
import serial
 
date = datetime.datetime.now()
date = str(date)
date = date[2:date.index(".")]
print(date)
bt_Module = serial.Serial('COM5', 9600)

try:
    for char in date:
        bt_Module.write(bytes(char,'utf-8'))
    bt_Module.write(b'\n')
except:
    pass
finally:
    bt_Module.close()
