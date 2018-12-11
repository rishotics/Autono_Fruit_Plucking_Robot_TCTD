
#include <ros.h>
#include <Servo.h>
#include <Encoder.h>


#define sharp_sensor
#define servo_pin 
#define PitchUp_pin 
#define PitchDown_pin 
#define ExtendFor_pin 
#define ExtendBack_pin

Servo myservo;  // create servo object to control a servo
long int left_position
long int right_position

void setup() 
{
  pinMode(sharp_sensor,INPUT);
  pinMode(servo_pin,OUTPUT);
  pinMode(PitchUp_pin,OUTPUT);
  pinMode(PitchDown_pin,OUTPUT);
  pinMode(ExtendFor_pin,OUTPUT);
  pinMode(ExtendBack_pin,OUTPUT);
  
  myservo.attach(servo_pin);  // attaches the servo on pin 9 to the servo object 
  Encoder knobLeft(L_encoder_1,L_encoder_2);     // initializing the left encoder intrrupt pins
  Encoder knobRight(R_encoder_1,R_encoder_2);  // initializing the right encoder interrupt pins

  ros::NodeHandle nh;
  
}

int sharp() 
  {
  float volts = analogRead(sharp_sensor)*0.0048828125;  // value from sensor * (5/1024)
  distance = 26*pow(volts, -1); // worked out from datasheet graph
  return distance;
  }


int servo_move(int angle, int curr_angle) 
{  
curr_angle = curr_angle + angle; // assuming servo 0 as right most point                                    
myservo.write(curr_angle);
delay (100); 
return curr_angle
}

void read_encoder()
{
  right_position = knobRight.read();
  left_position = knobRight.read();
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



