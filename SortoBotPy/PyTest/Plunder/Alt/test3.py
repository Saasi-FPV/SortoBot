import cv2
import numpy as np
import time

def get_color_after_delay():
    # Öffnen der Webcam
    cap = cv2.VideoCapture(0)

    # Erfassen eines Einzelbildes von der Webcam
    ret, frame = cap.read()

    # Warten für 1 Sekunde
    time.sleep(3)

    # Erfassen der Farbe im Zentrum des Bildes
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    height, width, _ = frame.shape
    center_x = width // 2
    center_y = height // 2
    color = hsv[center_y, center_x]
    
    # Konvertieren der Farbe von HSV zu BGR
    bgr = cv2.cvtColor(np.uint8([[color]]), cv2.COLOR_HSV2BGR)
    b, g, r = bgr[0][0]
    
    # Ausgabe der Farbe
    print("HSV:", color)
    print("BGR:", (b, g, r))

    # Freigeben der Webcam
    cap.release()

# Beispielaufruf der Funktion
get_color_after_delay()
