#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3);
ros::NodeHandle  nh;

geometry_msgs::Twist twist;
geometry_msgs::Vector3 v1;
geometry_msgs::Vector3 v2;
ros::Publisher send_vel("/turtle1/cmd_vel", &twist);
char val;

void setup()
{
  nh.initNode();
  nh.advertise(send_vel);
  MyBlue.begin(9600); 
}

void parseCommand(char input) {
  switch (input) {
    case '1': // LEFT
      v1.x = -2.0; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0; 
      break;
    case '2': // UP
      v1.x = 0.0; 
      v1.y = 2.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    case '3': // RIGHT
      v1.x = 2.0; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    case '4': // DOWN
      v1.x = 0.0; 
      v1.y = -2.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    case '5': // STOP
      v1.x = 0.0; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    case '6': // START
      //pause();
      break;  
    case 's': // SQUARE
      //hop();
      break; 
    case 't': // TRIANGLE
      //skip();
      break;  
    case 'x': // X
      //jump();
      break;
    case 'c': // CIRCLE
      //crawl();
      break;
  }
}

void loop()
{
   if (MyBlue.available()){ 
   val = MyBlue.read();  
    Serial.println(val); // Use the IDE's Tools > Serial Monitor
    parseCommand(val); // parse the input
  }
  twist.linear = v1;
  twist.angular = v2;
  send_vel.publish(&twist);
  nh.spinOnce();
}
