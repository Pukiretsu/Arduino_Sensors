import serial

bt_Module = serial.Serial('COM5', 9600)
print(bt_Module.portstr)
bt_Module.write(b"Bro moment")
bt_Module.close()



