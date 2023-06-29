import serial
import pandas as pd
import time

onPosAwnser = 'onPosition\r\n'

ser1 = serial.Serial('com6', 115200)
ser2 = serial.Serial('com?', 115200)

#test
color = 'red'


def doPath(pathNr):
    
    pathOfPath = "Paths\\Path" + str(pathNr) + ".csv"

    path = pd.read_csv(pathOfPath)

    for i in range(len(path)):

        xczmStr = 'x' + str(path.values[i][0]) + ' c' + str(path.values[i][1]) + ' z' + str(path.values[i][2]) + ' m' + str(path.values[i][3])

        print(xczmStr)
        ser1.write(xczmStr.encode())
        
        time.sleep(2)

        while(True):
            
            data = ser1.readline()
            data = data.decode()
            if data == onPosAwnser:
                print("onPos")
                break

def waitOnConveyStat():
    while(True):
        
        data2 = ser2.readline()
        data2 = data2.decode()
        if data2 == '1':
            print("ConveyerStat = 1")
            break


while(True):

    
    
    
    
    while(True):
        print("Start? Ja=[j] ")
        if input() == "j":
            print("Start Programm... ")
            break
    

   
    doPath(0)
    waitOnConveyStat()
    doPath(1)
    doPath(2)

    if (color == 'red'):
        doPath(3)




    print("End? Ja=[j] ")
    if input() == "j":
        print("End Programm... ")
        doPath(5)
        break
ser1.close()
