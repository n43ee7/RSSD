# UNOFFICIAL CODE [DO NOT RUN]

import serial
import os

def serialSearch():
    os.
with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:
    while True:
        led_on = input('Do you want the LED on? ')[0]
        if led_on in 'yY':
            ser.write(bytes('YES\n','utf-8'))
        if led_on in 'Nn':
            ser.write(bytes('NO\n','utf-8'))

 # A
import serial, time
arduino = serial.Serial('COM1', 115200, timeout=.1)
time.sleep(1) #give the connection a second to settle
arduino.write("Hello from Python!")
while True:
	data = arduino.readline()
	if data:
		print data.rstrip('\n') #strip out the new lines for now
		# (better to do .read() in the long run for this reason
        
# B
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
for p in ports:
    print p # Debugger
        if "Arduino" in p.description:
            print "This is an Arduino!"
 
 # C
    import warnings
import serial
import serial.tools.list_ports

arduino_ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if 'Arduino' in p.description  # may need tweaking to match new arduinos
]
if not arduino_ports:
    raise IOError("No Arduino found")
if len(arduino_ports) > 1:
    warnings.warn('Multiple Arduinos found - using the first')

ser = serial.Serial(arduino_ports[0])

# D (Ref https://stackoverflow.com/questions/24214643/python-to-automatically-select-serial-ports-for-arduino)
import serial.tools.list_ports

def find_arduino(serial_number):
    for pinfo in serial.tools.list_ports.comports():
        if pinfo.serial_number == serial_number:
            return serial.Serial(pinfo.device)
    raise IOError("Could not find an arduino - is it plugged in?")

ser = find_arduino(serial_number='85430353531351B09121')
