#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h> //required for Twist message definition
#include <SoftwareSerial.h> 

//declaration for serial communication with HC-05
SoftwareSerial MyBlue(2, 3);

//declaring ROS node object
ros::NodeHandle  nh;

//declaring Twist msg object
geometry_msgs::Twist twist;

//decleration of v3 object for linear velocities
geometry_msgs::Vector3 v1;

//declaration for angular velocities
geometry_msgs::Vector3 v2;

//publishing topic and msg type decleration
ros::Publisher send_vel("/cmd_vel", &twist);

//varialble for switch case
char val;

void setup()
{
  nh.initNode();  //rosnode initialization
  nh.advertise(send_vel);
  MyBlue.begin(9600); //baud rate for communication with HC-05
}

void parseCommand(char input) {
  switch (input) {
    case '1': // LEFT
      v1.x = 0.0; //linear vector values
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;//angular vector values
      v2.y = 0.0;
      v2.z = 1.0; 
      break;
    case '2': // UP
      v1.x = 0.3; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    case '3': // RIGHT
      v1.x = 0.0; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = -1.0;
      break;
    case '4': // DOWN
      v1.x = -0.3; 
      v1.y = 0.0;
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
    default:
      v1.x = 0.0; 
      v1.y = 0.0;
      v1.z = 0.0;
      v2.x = 0.0;
      v2.y = 0.0;
      v2.z = 0.0;
      break;
    
  }
}

void loop()
{
   if (MyBlue.available()){ 
   val = MyBlue.read();  
    Serial.println(val); 
    parseCommand(val); // parse the input
  }
  twist.linear = v1;
  twist.angular = v2;
  send_vel.publish(&twist); //publishing Twist message on node
  nh.spinOnce();
}
