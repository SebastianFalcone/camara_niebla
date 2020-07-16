import serial
import time
import os

#Defino el nombre del archivo
fileName="test.txt"

#Elijo el puerto del arduino, la velocidad de transferencia
arduino_port = "/dev/ttyACM0"
baud = 115200

#Genero el objeto para manejar las lecturas
ser = serial.Serial(arduino_port, baud)

#Hago un flush para liberar el cache del puerto
ser.flushInput()

print("Conectando al puerto del Arduino:" + arduino_port)

#Abro o creo el archivo
file = open(fileName, "a+")

print("Archivo creado/abierto con exito")

#Leo la cantidad de lineas que tiene el archivo
line = len(file.readlines())

while True:
    try:
        #Leo el stream de datos proveniente del arduino
        data = ser.readline()         

        #Si solo existe una linea (archivo vacio) pongo los headers
        if line == 1:
            print("Poniendo Headers")
            file.write("Timestamp TempAnalog TempDig HumDig \n")
        
        else:
            print("Linea " + str(line-1) + ":") 


            #time.time() es un float, lo casteo a integer y despues a string (es mas facil usar el ptrint y write con strings)
            timestmp = str(int(time.time()))

            #Preeliminar de lo que se va a mandar al archivo
            print(timestmp + data) 

            #Escribo en el archivo el timestamp y despues la data del arduino, el flush libera el buffer (sino no se actualiza el archivo)
            file.write(str(int(time.time())) + data)    
            file.flush()

        #Esto no es tan necesario pero es para ir llevando un registro de cuantas lineas van escritas
        line = line + 1
    
    except:
        print("Programa finalizado!")
        #Importante cerrar el archivo o pueden quedar cosas en el buffer
        file.close()
        break