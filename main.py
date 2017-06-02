#!/usr/bin/python

import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)

# We wait here because connecting to the Arduino takes a moment.
time.sleep(2.5)

ser.write('0,1000,2,255-1,2000,2,255-2,100,2,255-1,100,5,64-')
