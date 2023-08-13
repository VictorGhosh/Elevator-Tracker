#!/usr/bin/env python3
import serial
from datetime import datetime as dt

port = None

def connect():
    try:
        global port
        port = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        port.reset_input_buffer()
        return
    
    except:
        print('Failed to connect to port')
        exit()

if __name__ == '__main__':
    connect()

    fName = dt.now().strftime("%d-%m-%Y_%H-%M-%S.txt")

    while True:
        try:
            if port.in_waiting > 0:
                nl = port.readline().decode('utf=8').rstrip()

                with open(fName, 'a+') as f:
                    f.write(nl)
                    f.write('\n')
                
                print(nl)
        
        except:
            print('Failed to read from port')
            exit()
