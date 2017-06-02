#!/usr/bin/python

import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)

time.sleep(2.5)

ser.write('0,500,2,255')

time.sleep(.1)

ser.write('1,500,2,255')

time.sleep(.1)

ser.write('2,500,2,255')
