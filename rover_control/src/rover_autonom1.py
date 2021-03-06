#!/usr/bin/env python

import roslib
import rospy
import actionlib
from std_msgs.msg import String
from sensor_msgs.msg import NavSatFix
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
from geographic_msgs.msg import WayPoint
#move_base_msgs
from move_base_msgs.msg import *
from rover_control.msg import Distancewithangle
import math
from math import radians, cos, sin, asin, sqrt, pow, pi, atan2


xold=0
yold=0

def callback_dist(msg):

    global xold
    global yold

 
    WPx =msg.pose.position.x
    WPy=msg.pose.position.y
    
    print(str(WPx))
    
    if(WPx != xold or WPy != yold):
        move_base(WPx,WPy)

    xold=WPx
    yold=WPy

      
 

def move_base(x,y):

        sac = actionlib.SimpleActionClient('move_base', MoveBaseAction )
        goal = MoveBaseGoal()
        rospy.loginfo("Move base started x: %s y: %s" ,str(x),str(y))

        goal.target_pose.pose.position.x =  float(x)
        goal.target_pose.pose.position.y =  float(y)
        goal.target_pose.pose.orientation.w = 1.0
        goal.target_pose.header.frame_id = 'odom'
        goal.target_pose.header.stamp = rospy.Time.now()

        #start listner
        sac.wait_for_server()

         #send goal
        sac.send_goal(goal)

        #finish
        sac.wait_for_result()
        print sac.get_result()

def main():
    rospy.init_node('simple_move')
    rate = rospy.Rate(0.05)
    while not rospy.is_shutdown():
    	rospy.Subscriber("/goal", PoseStamped, callback_dist)
    	rate.sleep()




if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        print "Keyboard Interrupt"
