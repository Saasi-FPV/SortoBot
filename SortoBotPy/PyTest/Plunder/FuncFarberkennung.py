import cv2
import numpy as np
import time

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





# Beispielaufruf der Funktion mit einer Dauer von 1 Sekunde und einem Toleranzbereich von 40
color = erkennen_farbe(get_stable_color(1, 40))
print(color)

