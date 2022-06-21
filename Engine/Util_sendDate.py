import calendar
import datetime
import serial
 
date = datetime.datetime.utcnow()
utc_time = calendar.timegm(date.utctimetuple())
BTData = str(utc_time)

bt_Module = serial.Serial('COM5', 9600)

try:
    for char in BTData:
        bt_Module.write(bytes(char,'utf-8'))
    bt_Module.write(b'\n')
except:
    pass
finally:
    bt_Module.close()
