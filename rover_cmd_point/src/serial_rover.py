#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import roslib
import serial
from rover_send_point.msg import Serialmsg
from serial import SerialException



class SerialNode(object):
	def __init__(self):
		rospy.init_node('serial_node', anonymous=True)
		self.serialmsg = Serialmsg()
		rospy.spin()
		self.serial_init()

	def callback_cmd(self,data):
		#rospy.loginfo( "I heard %s",data.motor)
		self.serialmsg.motor=data.motor
		ser.write(self.serialmsg.motor)

	def serial_init(self):
	
		if(portIsUsable('/dev/ttyACM0')==True):
			ser = serial.Serial('/dev/ttyACM0', 9600)
			ser.open()
			rospy.Subscriber("/rover_serialcmd", Serialmsg, self.callback_cmd)
		else:
			print("port cant opened!")
    
   def portIsUsable(portName):
    	try:
      		ser = serial.Serial(port=portName)
       		return True
    	except:
       		return False
		
                
		 	
if __name__ == '__main__':
	 	SerialNode()
	 	

      
