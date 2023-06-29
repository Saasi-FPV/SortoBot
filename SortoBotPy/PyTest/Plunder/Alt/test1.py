import cv2
import numpy as np

def get_color(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        color = hsv[y, x]
        print("HSV:", color)
        
        bgr = cv2.cvtColor(np.uint8([[color]]), cv2.COLOR_HSV2BGR)
        b, g, r = bgr[0][0]
        print("BGR:", (b, g, r))
        
        cv2.circle(frame, (x, y), 5, (0, 255, 0), -1)
        cv2.imshow('frame', frame)

# Öffnen der Webcam
cap = cv2.VideoCapture(0)

cv2.namedWindow('frame')
cv2.setMouseCallback('frame', get_color)

while True:
    # Erfassen eines Einzelbildes von der Webcam
    ret, frame = cap.read()
    
    # Anzeigen des aktuellen Frames
    cv2.imshow('frame', frame)
    
    # Beenden der Schleife, wenn die 'q'-Taste gedrückt wird
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Freigeben der Webcam und Schließen aller Fenster
cap.release()
cv2.destroyAllWindows()
