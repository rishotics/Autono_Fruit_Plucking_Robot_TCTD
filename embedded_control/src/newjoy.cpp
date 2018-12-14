#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
// #include "geometry_msgs/Twist.h"
// #include "std_msgs/Int64.h"
ros::Publisher converter_pub ;
ros::Subscriber converter_sub ;
sensor_msgs::Joy  msg1;
void controller_callback(const sensor_msgs::Joy::ConstPtr& msg);
int i =0 ;
int flag = 0;
int counter = 0;
int main (int argc,char **argv)
{
    
	ros::init(argc, argv, "converter");
	ros::NodeHandle n;
    converter_pub = n.advertise<sensor_msgs::Joy>("new_joy",1000);
	converter_sub = n.subscribe("/joy",1000,controller_callback);
    ros::Rate loop_rate(10.0);
    loop_rate.sleep();
   while(ros::ok())
	{
	// controller_pub.publish(out_msg1);
	ros::spinOnce();
	// ROS_INFO("%f", vel_msg.linear.x);
	loop_rate.sleep();	
	}

}
void controller_callback(const sensor_msgs::Joy::ConstPtr& msg)
{  
   if (counter == 0)
   {
   	counter ++;
   	msg1 = *msg;
   	converter_pub.publish(msg1);
   	return ;
   }

 for  (i=0;i<=10;++i)
    {  if  (msg->buttons[i] != msg1.buttons[i] )
 	  {
 	  	flag =1;
 	  }
 	}
for  (i=0;i<=7;++i)
   {if  (msg->axes[i] != msg1.axes[i] )
 	  {
 	  	flag =1;
 	  }
   }
    msg1 = *(msg);
    ROS_INFO ("Check");
  if (flag == 1 )
  {
    converter_pub.publish(msg1);
  }

}

