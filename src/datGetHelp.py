#!/usr/bin/env python3
import serial
import time

port = None

def connect():
    try:
        global port
        port = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        port.reset_input_buffer()
        return
    
    except:
        print("datGetHelp.py: Failed to connect to port");
        exit()

if __name__ == '__main__':
    connect()

    while True:
        try:
            if port.in_waiting > 0:
                line = port.readline().decode('utf=8').rstrip()
            
                f = open("buff.txt", "w")
                f.write(line)
                f.close()
                time.sleep(0.25)
   
        except:
            print("datGetHelp.py: Failed to read from port");
            time.sleep(1)
            connect()
