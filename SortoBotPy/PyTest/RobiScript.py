import serial
import pandas as pd
import time
import cv2
import numpy as np
import threading



onPosAwnser = 'onPosition\r\n'

ser1 = serial.Serial('com6', 115200)
ser2 = serial.Serial('com5', 115200)



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
        requestmsg = "request"
        ser2.write(requestmsg.encode())
        data2 = ser2.readline()
        data2 = data2.decode()
        if data2 == '1\r\n':
            print("ConveyerStat = 1")
            break


def get_stable_color(duration, tolerance):
    # Öffnen der Webcam
    cap = cv2.VideoCapture(0)

    # Aktuelle Zeit
    start_time = time.time()

    stable_color = None
    stable_duration = 0

    while stable_duration < duration:
        # Erfassen eines Einzelbildes von der Webcam
        ret, frame = cap.read()

        # Erfassen der Farbe im Zentrum des Bildes
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        height, width, _ = frame.shape
        center_x = width // 2
        center_y = height // 2
        color = hsv[center_y, center_x]

        # Überprüfen, ob die Farbe stabil ist
        if stable_color is None:
            stable_color = color
        elif np.allclose(color, stable_color, atol=tolerance):
            stable_duration = time.time() - start_time
        else:
            stable_color = color
            start_time = time.time()

    # Konvertieren der stabilen Farbe von HSV zu BGR
    bgr = cv2.cvtColor(np.uint8([[stable_color]]), cv2.COLOR_HSV2BGR)
    b, g, r = bgr[0][0]

    # Freigeben der Webcam
    cap.release()
    return bgr[0][0]


def erkennen_farbe(bgr_farbe):
    rot = bgr_farbe[2]
    gruen = bgr_farbe[1]
    blau = bgr_farbe[0]

    if rot > gruen and rot > blau:
        return "Rot"
    elif blau > rot and blau > gruen:
        return "Blau"
    else:
        return "Grün"

def eingabe_thread():
    global eingabe
    eingabe = 'n'
    eingabe = input("Programm beenden? [j] = Ja: ")





#ProgrammStart


while(True):
    print("Start? Ja=[j] ")
    if input() == "j":
        print("Start Programm... ")
        break

eingabe_thread = threading.Thread(target=eingabe_thread)
eingabe_thread.start()

while(True):

 
    doPath(0)
    waitOnConveyStat()
    print("End? Ja=[j] ")
    if eingabe == "j":
        break
    doPath(1)
    doPath(2)

    time.sleep(5)
    color = erkennen_farbe(get_stable_color(1, 40))
    print(color)

    if (color == 'Rot'):
        doPath(3)

    if (color == 'Blau'):
        doPath(4)

    if (color == 'Grün'):
        doPath(5)




    print("End? Ja=[j] ")
    if eingabe == "j":
        break



#ProgrammEnde
print("Fahre auf Reverenz ")
while(True):
    print("Weg frei? Ja=[j] ")
    if input() == "j":
        print("Verfahre......")
        break
doPath(6)
print("End Programm... ")
ser1.close()
eingabe_thread.join()
