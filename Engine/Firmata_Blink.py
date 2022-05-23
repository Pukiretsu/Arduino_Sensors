import pyfirmata
import keyboard
import time
import random

board = pyfirmata.Arduino('COM3')

def rainbow(board):
    sleeptime = 0.09
    for i in range(random.randint(1,5)):
        
        board.digital[9].write(1)
        board.digital[11].write(0)
        time.sleep(sleeptime)

        board.digital[10].write(1)
        board.digital[9].write(0)        
        time.sleep(sleeptime)
        
        board.digital[11].write(1)
        board.digital[10].write(0)
        time.sleep(sleeptime)
        
    board.digital[9].write(0)        
    board.digital[10].write(0)
    board.digital[11].write(0)
    time.sleep(0.3)

while True:
    try:
        if keyboard.is_pressed('a'):
            board.digital[9].write(1)
        else:
            board.digital[9].write(0)
        
        if keyboard.is_pressed('s'):
            board.digital[10].write(1)
        else:
            board.digital[10].write(0)
            
        if keyboard.is_pressed('d'):
            board.digital[11].write(1)
        else:
            board.digital[11].write(0)
        
        if keyboard.is_pressed('r'):
            rainbow(board)
        
        if keyboard.is_pressed('q'):
            board.digital[9].write(0)
            board.digital[10].write(0)
            board.digital[11].write(0)
            board.exit()
            break
    
    except:
        board.exit()
        break
    
    