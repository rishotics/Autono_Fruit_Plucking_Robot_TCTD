/*
subscribing from topic "/joy" via controller_sub
publishing to topic "cmd_vel_joy" via controller_pub
node name - "joy_publisher"
Y-linear x incremented by 30
A-linear x decremented by 30
X-angular z incremented by 30
B-angular z decremented by 30
LB- emergency stop
RB- all velocity zero and estop release
LT- axes 2 [-1 to 1] [1 when unpressed] MANUAL MODE
RT- axes 5 [-1 to 1] [1 when unpressed] AUTONOMOUS MODE
Twist message if angular.y=0 then manual and if angular.y=1 then autonomous
*/
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int64.h"
using namespace std;

#define r 0.5
#define d 1


ros::Publisher controller_pub;
ros::Subscriber controller_sub;
geometry_msgs::Twist vel_msg;
geometry_msgs::Twist out_msg1;

int a =0;
int flag = 0;

int vl=0;
int vr=0;
int v =0;
int omega = 0;
int z =0;
void controller_callback(const sensor_msgs::Joy::ConstPtr& msg);


int main(int argc,char **argv)
{

	ros::init(argc, argv, "joy_publisher");
	ros::NodeHandle n;

	
	controller_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_joy",1000);
	controller_sub = n.subscribe("/joy",1000,controller_callback);
	

	ros::Rate loop_rate(10.0);

	vel_msg.linear.x=0;
	z=0;
	vel_msg.linear.y=0;
	out_msg1.linear.z=90;
	out_msg1.angular.x=0;
	out_msg1.angular.y=0;
	
	controller_pub.publish(out_msg1);
	
	loop_rate.sleep();	

	while(ros::ok())
	{
	controller_pub.publish(out_msg1);
	ros::spinOnce();
	// ROS_INFO("%f", vel_msg.linear.x);
	loop_rate.sleep();	
	}
	return 0;

}

void controller_callback(const sensor_msgs::Joy::ConstPtr& msg)
{
	ROS_INFO("%f", vel_msg.linear.x);
	if(a==1){
		vel_msg.linear.x = 0;
		z = 0;
	}

	if(msg->buttons[3]==1)
	(vel_msg.linear.x)=vel_msg.linear.x+30;
	
	if(msg->buttons[0]==1)
	(vel_msg.linear.x)=vel_msg.linear.x-30;

	if(msg->buttons[2]==1)
	(z)=z+30;

	if(msg->buttons[1]==1)
	(z)=z-30;


    if (msg->buttons[4]==1)
    	out_msg1.linear.z = out_msg1.linear.z + 5 ;   // yeh wla servo ka angle hain  

     if (msg->buttons[5]==1)                         //  yeh wla bhi servo ka hain 
    	out_msg1.linear.z = out_msg1.linear.z - 5 ;
 	
    if (msg->axes[7]==1 )
    	out_msg1.angular.x = 1-out_msg1.angular.x;   // YEH WLA pitch linear actuator ka hain 


    if (msg->axes[7]==-1 )
        out_msg1.angular.x = -1 - out_msg1.angular.x;

    if (msg->axes[6]==1 )
    	out_msg1.angular.y = 1-out_msg1.angular.y;    //yeh wla extender ka hain 


    if (msg->axes[6]==-1 )
     	out_msg1.angular.y = -1 - out_msg1.angular.y;

    
    if (msg->axes[2] == -1 )
     	out_msg1.angular.z = -1 - out_msg1.angular.z;   // yeh wla gripper ka hain  

	if(msg->axes[5]== -1)
	{
	
	//estop
	// (vel_msg.angular.y)=1;
	vel_msg.linear.y=0;
	z=0;
	vel_msg.linear.x=0;
	
	out_msg1.angular.x=0;
	out_msg1.angular.y=0;
		vel_msg.linear.y=0;
	z=0;
	vel_msg.linear.x=0;
	out_msg1.angular.x=0;
	out_msg1.angular.y=0;
	ROS_INFO("STOP ");

	}
	
	// else if((msg->buttons[10]==1) && flag == 1)
	// {
	//                                                 //estop release
	// flag = 0;
	// vel_msg.linear.y=0;
	// z=0;
	// vel_msg.linear.x=0;
	// out_msg1.angular.x=0;
	// out_msg1.angular.y=0;
	// ROS_INFO("EStop Release ");
	// }
	v = vel_msg.linear.x;
 	omega = z;

  	vl = (2*v - d*omega)/2;
  	vr = (2*v + d*omega)/2;

  	// out_msg1.angular.y = vel_msg.angular.y;		// variable to check for estop
  	out_msg1.linear.y = vr*60/(2*3.1415*30*r);  // rpm = 30
  	out_msg1.linear.x = vl*60/(2*3.1415*30*r);
  

	//controller_pub.publish(vel_msg);

	//ROS_INFO("%f", vel_msg.linear.x);
}

