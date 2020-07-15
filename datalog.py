import serial

arduino_port = "/dev/ttyACM0" #serial port of Arduino
baud = 115200 #arduino uno runs at 9600 baud
fileName="test.txt" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")

samples = 10 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
while True:
    try:
        if print_labels:
            if line==0:
                print("Printing Column Headers")
            else:
                print("Line " + str(line) + ": writing...")
        getData=str(ser.readline())
        data=getData[0:][:-2]
        print(data)

        file = open(fileName, "a")
        file.write(data + "\n") #write data with a newline
        line = line+1
    
    except:
        print("Data collection complete!")
        file.close()
        break