
#include <ros.h>
#include <std_msgs/Int64.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>
#include <Encoder.h>
#include <embedded_control/sensor_data.h>


#define sharp_sensor A0
#define servo_gripper 10
#define servo_pin 11
#define servo_seeding 6
#define PitchUp_pin 27
#define PitchDown_pin 29 
#define ExtendFor_pin 31
#define ExtendBack_pin 33
#define pressure_pin A1 

#define L_encoder_1 7
#define L_encoder_2 2
#define R_encoder_1 3
#define R_encoder_2 5
#define Left_DIR 35
#define Right_DIR 39
#define Left_BRK 37
#define Right_BRK 41
#define k 500
#define left_PWM 8
#define right_PWM 9

Servo myservo;  // create servo object to control a servo
Encoder knobLeft(L_encoder_1,L_encoder_2);
Encoder knobRight(R_encoder_1,R_encoder_2);

long int left_position;
long int right_position;
int servo_test;
int angle , curr_angle; //// yeh wala bas check karne ke liye hain

ros::NodeHandle nh;
embedded_control::sensor_data pub_msg;

void messageCb( const geometry_msgs::Twist& vel_msg){

  int left_pwm,right_pwm;
  
  if (vel_msg.linear.x<=0 && vel_msg.linear.y<=0)
  {
  left_pwm = -(vel_msg.linear.x);
  right_pwm = -(vel_msg.linear.y);
  Backward(left_pwm,right_pwm);
  }
  
  if (vel_msg.linear.x>0 && vel_msg.linear.y>0)
  {
  left_pwm = (vel_msg.linear.x);
  right_pwm = (vel_msg.linear.y);
  Forward(left_pwm,right_pwm);
  }

  if (vel_msg.linear.x<0 && vel_msg.linear.y>0)
  {
  left_pwm = -(vel_msg.linear.x);
  right_pwm = (vel_msg.linear.y);
  Left(left_pwm,right_pwm);
  }
  
  if (vel_msg.linear.x>0 && vel_msg.linear.y<0)
  {
  left_pwm = (vel_msg.linear.x);
  right_pwm = -(vel_msg.linear.y);
  Right(left_pwm,right_pwm);
  }

  myservo.write (vel_msg.linear.z);
  servo_test = vel_msg.linear.z;
  
  if  (vel_msg.angular.x == 1)
   {  PitchUp();
    }
   if  (vel_msg.angular.x == 0)
   {  PitchStop();
    }
   if (vel_msg.angular.x == -1)
   { PitchDown();
    }
      if  (vel_msg.angular.y == 1)
   {  ExtenderForward();
    }
   if  (vel_msg.angular.y == 0)
   {  ExtenderHalt();
    }
   if (vel_msg.angular.y == -1)
   { ExtenderBack();
    }
   
}

ros::Publisher arduino_pub("feedback_data", &pub_msg);
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel_joy", &messageCb );


void setup() 
{
  pinMode(sharp_sensor,INPUT);
  pinMode(servo_pin,OUTPUT);
  pinMode(PitchUp_pin,OUTPUT);
  pinMode(PitchDown_pin,OUTPUT);
  pinMode(ExtendFor_pin,OUTPUT);
  pinMode(ExtendBack_pin,OUTPUT);
  pinMode (Left_DIR,OUTPUT);
  pinMode (Right_DIR,OUTPUT);
  pinMode (Left_BRK,OUTPUT);
  pinMode (Right_BRK,OUTPUT);
  
  myservo.attach(servo_pin);  // attaches the servo on pin 9 to the servo object 
  myservo.write(90);
 // Encoder knobLeft(L_encoder_1,L_encoder_2);     // initializing the left encoder intrrupt pins
  //Encoder knobRight(R_encoder_1,R_encoder_2);  // initializing the right encoder interrupt pins

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(arduino_pub);
  
  
  
}
int pressure ()
{
  int val = analogRead(pressure_pin);
  return val*k;
}
int sharp() 
  {
;    int distance;
  float volts = analogRead(sharp_sensor)*0.0048828125;  // value from sensor * (5/1024)
  distance = 26*pow(volts, -1); // worked out from datasheet graph
  return distance;
  }


int servo_move(int angle, int curr_angle) 
{  
curr_angle = curr_angle + angle; // assuming servo 0 as right most point                                    
myservo.write(curr_angle);
delay (100); 
return curr_angle;
}

void read_encoder()
{
  right_position = knobRight.read();
  left_position = knobLeft.read();
}

void PitchUp ()
{
  digitalWrite (PitchUp_pin,HIGH);
  digitalWrite (PitchDown_pin,LOW);
}

void PitchDown ()
{
  digitalWrite (PitchUp_pin,LOW);
  digitalWrite (PitchDown_pin,HIGH);
}

void PitchStop()
{
  digitalWrite (PitchUp_pin,LOW);
  digitalWrite (PitchDown_pin,LOW);
}
void ExtenderForward ()
{
  digitalWrite (ExtendFor_pin,HIGH);
  digitalWrite (ExtendBack_pin,LOW);
}

void ExtenderBack ()
{
  digitalWrite (ExtendFor_pin,LOW);
  digitalWrite (ExtendBack_pin,HIGH);
}

void ExtenderHalt()
{
  digitalWrite (ExtendFor_pin,LOW);
  digitalWrite (ExtendBack_pin,LOW);
}
void Forward(int left_pwm,int right_pwm)
{
  digitalWrite(Left_DIR,HIGH);
  digitalWrite(Right_DIR,LOW);
  analogWrite(left_PWM,left_pwm);
  analogWrite(right_PWM,right_pwm);
}

void Backward(int left_pwm,int right_pwm)
{
  digitalWrite(Left_DIR,LOW);
  digitalWrite(Right_DIR,HIGH);
  analogWrite(left_PWM,left_pwm);
  analogWrite(right_PWM,right_pwm);
}

void Right(int left_pwm,int right_pwm)
{
  digitalWrite(Left_DIR,HIGH);
  digitalWrite(Right_DIR,HIGH);
  analogWrite(left_PWM,left_pwm);
  analogWrite(right_PWM,right_pwm);
}

void Left(int left_pwm,int right_pwm)
{
  digitalWrite(Left_DIR,LOW);
  digitalWrite(Right_DIR,LOW);
  analogWrite(left_PWM,left_pwm);
  analogWrite(right_PWM,right_pwm);
}

void halt()
{
  digitalWrite(Left_BRK,HIGH);
  digitalWrite(Right_BRK,HIGH);
}


void motor_linear (int speed )
{ 

  int pwm = k *speed  ;   ///idhar scalling factor lagana hain 

}

void loop()
{
  pub_msg.sharp_ir = sharp();
  pub_msg.L_encoder = -knobLeft.read();
  pub_msg.R_encoder = knobRight.read();
  //pub_msg.servo_angle = servo_move(angle,curr_angle);
  pub_msg.servo_angle = servo_test;
  pub_msg.pressure = pressure ();
  arduino_pub.publish( &pub_msg );
  
  nh.spinOnce();
//  delay(20); 

}

