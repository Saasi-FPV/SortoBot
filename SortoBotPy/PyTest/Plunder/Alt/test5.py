import cv2
import numpy as np
import time

def get_stable_color(duration, tolerance):
    # Öffnen der Webcam
    cap = cv2.VideoCapture(1)

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

    # Farbe anhand der BGR-Werte bestimmen
    if r > 150 and g < 150 and b < 150:
        color_name = "Rot"
    elif r < 150 and g > 150 and b < 150:
        color_name = "Grün"
    elif r < 150 and g < 150 and b > 150:
        color_name = "Blau"
    elif r < 150 and g < 150 and b < 150:
        color_name = "Gelb"
    elif r > 200 and g > 200 and b > 200:
        color_name = "Weiß"
    elif r < 150 and g < 150 and b < 150:
        color_name = "Schwarz"
    else:
        color_name = "Unbekannt"

    # Ausgabe der stabilen Farbe
    print("BGR:", (b, g, r))
    print("Farbe:", color_name)

    # Freigeben der Webcam
    cap.release()

# Beispielaufruf der Funktion mit einer Dauer von 1 Sekunde und einem Toleranzbereich von 10
get_stable_color(1, 10)
