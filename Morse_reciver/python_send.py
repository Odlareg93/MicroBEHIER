import serial
ser = serial.Serial('COM3', 9600,timeout=.1)
ser.write('SOS'.encode())