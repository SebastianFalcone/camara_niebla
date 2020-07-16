import serial
import time
import os

fileName="test.txt"

arduino_port = "/dev/ttyACM0" #serial port of Arduino
baud = 115200
ser = serial.Serial(arduino_port, baud)
ser.flushInput()

print("Connected to Arduino port:" + arduino_port)

file = open(fileName, "a+")
print("Created file")

line = len(file.readlines())
while True:
    try:
        
        data = ser.readline()         

        if line == 1:
            print("Poniendo Headers")
            file.write("Timestamp TempAnalog TempDig HumDig \n")
        
        else:
            print("Linea " + str(line-1) + ":...") 
            print(str(int(time.time())) + data) 

            file.write(str(int(time.time())) + data)    
        
        line = line + 1
    
    except:
        print("Programa finalizado!")
        file.close()
        break