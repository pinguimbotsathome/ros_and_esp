//Codigo na esp

#include <ros.h>
#include <std_msgs/Int32.h>
//#include <esp32-hal-ledc.h>
#define USE_USBCON

ros::NodeHandle nh;

int pwmChannel= 0;
int pwmPin = 2;
int frequence = 1000; // 1KHz
int resolution = 8;

void vcc (const std_msgs::Int32 &PwmReceive){
  int valorPwm = PwmReceive.data;
  ledcAttachPin(pwmPin, pwmChannel);
  ledcWrite(pwmChannel, valorPwm);
  
}

ros::Subscriber<std_msgs::Int32> sub("PwmReceive", &vcc);

void setup() {
  nh.getHardware()->setBaud(115200);
  ledcSetup(pwmChannel, frequence, resolution);
  //delay(2000);

  nh.initNode();
  nh.subscribe(sub);
 
 
}

void loop() {
  nh.spinOnce();
  //while(!nh.connected()) {nh.spinOnce();}
}
