#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist


def pubTwist():
    rospy.init_node('pubTwist', anonymous=True)

    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(1)  # 1 Hz

    twist =  Twist()
    twist.linear.x = 0.5
    twist.angular.z = 0

    while not rospy.is_shutdown():
        pub.publish(twist)  
        rospy.loginfo("Linear: %f  Angular: %f", twist.linear.x, twist.angular.z) 
        rate.sleep()


if __name__ == '__main__':
    try:
        pubTwist()
    except rospy.ROSInterruptException:
        pass    

