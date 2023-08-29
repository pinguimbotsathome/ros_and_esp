#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
geometry_msgs::Twist msg;

float ros_linear;
float ros_ang;

int Xchannel = 25;
int Ychannel = 26;
int X_joy;  // = 105;
int Y_joy;  // = 105;


void ros_receiver(const geometry_msgs::Twist &cmd_vel){
  ros_linear = cmd_vel.linear.x;
  ros_ang = cmd_vel.angular.z;
  robotVelocity2joystick(ros_linear, ros_ang);

}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel",ros_receiver);

void setup() {
  Serial.begin(115200);

  //ros setup:
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);

}

void robotVelocity2joystick(float velLinear, float velAngular) {
  float velLinearMAX = 3.0;
  float velLinearMIN = -3.0;

  float velAngularMAX = 54.0;  // velAngular is negative clockwise on ROS
  float velAngularMIN = -velAngularMAX;


  Y_joy = 255 * (velLinear - velLinearMIN) / (velLinearMAX - velLinearMIN);
  X_joy = 255 * (velAngular - velAngularMIN) / (velAngularMAX - velAngularMIN);

  dacWrite(Xchannel, X_joy);
  dacWrite(Ychannel, Y_joy);
}

void loop() {
  nh.spinOnce();
}

