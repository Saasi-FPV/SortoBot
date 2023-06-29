import serial

# Öffnen der seriellen Verbindung zu Arduino
ser = serial.Serial('com7', 9600)  # Anpassen des Portnamens und der Baudrate entsprechend deiner Konfiguration

# Sende Daten an den Arduino
ser.write(b'hello')

# Warte auf den Empfang von Daten vom Arduino
data = ser.readline()
data = data.decode()
test = 'onPosition\r\n'
if data == test:
    print(data)
print(data)
print(test)
print(data == test)

#print('Received:', data.decode())

# Schließe die serielle Verbindung
ser.close()
