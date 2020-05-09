import serial.tools.list_ports
import serial
import subprocess

ports = list(serial.tools.list_ports.comports())
for p in ports:
    if "Arduino" in p.description:
        print (p)

ser = serial.Serial(p.device, 9600,timeout=.1)
if(ser.isOpen() == False):
    ser.open()
command = ""

#Code Morse
# (.- A)	(-... B)	(-.-. C)	(-.. D)		(. E)	 (..-. F)   (--. G)   (.... H)   (.. I)   (.--- J)   (-.- K)   (.-.. L)
# (-- M)  (-.  N)   (--- O)   (.--. P)   (--.- Q)   (.-. R)   (... S)   (- T)  (..- U)   (...- V)   (.-- W)   (-..- X)   (-.-- Y)   (--.. Z)

ser.write('S'.encode())
while True:
	data = ser.readline()[:-2].decode("utf-8")
	if data:
		print (data)
		command += data
		if "FOX" in command:
			subprocess.call(['C:\Program Files (x86)\Mozilla Firefox\\firefox.exe'])
			command = ""
		if "NOT" in command:
			subprocess.call(['C:\Windows\\notepad.exe'])
			command = ""
		if "MPT" in command:
			subprocess.call(['C:\WINDOWS\system32\\mspaint.exe'])
			command = ""
