#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
geometry_msgs::Twist msg;

float move1;
float move2;

void move(const geometry_msgs::Twist &cmd_vel)
{
  move1 = cmd_vel.linear.x;
  move2 = cmd_vel.angular.z;
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel",move);

void setup()
{
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);

} 

void loop()
{
  nh.spinOnce();
}
