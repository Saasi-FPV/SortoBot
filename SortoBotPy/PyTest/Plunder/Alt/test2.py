import cv2
import numpy as np

def get_center_color(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    height, width, _ = frame.shape
    center_x = width // 2
    center_y = height // 2
    color = hsv[center_y, center_x]
    print("HSV:", color)
    
    bgr = cv2.cvtColor(np.uint8([[color]]), cv2.COLOR_HSV2BGR)
    b, g, r = bgr[0][0]
    print("BGR:", (b, g, r))

# Öffnen der Webcam
cap = cv2.VideoCapture(0)





while True:
    # Erfassen eines Einzelbildes von der Webcam
    ret, frame = cap.read()

    # Anzeigen des aktuellen Frames
    cv2.imshow('frame', frame)
    
    # Farbe im Zentrum des Bildes erfassen
    get_center_color(frame)

    # Beenden der Schleife, wenn die 'q'-Taste gedrückt wird
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Freigeben der Webcam und Schließen aller Fenster
cap.release()
