#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(2, 7);
//Encoder knobRight(5, 8);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
}
long prev =0;
long current =0;
unsigned long int t2 = 0;
long positionLeft  = -999;
long positionRight = -999;
int counter = 0;
unsigned long int t1;
int vel =0;
void manthan ()
{
  t1= millis();
  current = knobLeft.read();
  vel = (current-prev)/(t1 - t2);
  Serial.println(vel);
  t2 = t1 ;
  prev =current ;
}
void loop() {
  long newLeft, newRight;
     if (counter>10 )
     { counter =0;
      
       manthan();
     }
     delay(8);
////  newLeft = knobLeft.read();
////  current = newLeft;
////  newRight = knobRight.read();
//  if (newLeft != positionLeft || newRight != positionRight) {
//    Serial.print("Left = ");
//    Serial.print(newLeft);
////  Serial.print(", Right = ");
////  Serial.print(newRight);
////    Serial.println();
//    positionLeft = newLeft;
//  
////    positionRight = newRight;
//  }
//  // if a character is sent from the serial monitor,
//  // reset both back to zero.
//  if (Serial.available()) {
//    Serial.read();
//    Serial.println("Reset both knobs to zero");
//    knobLeft.write(0);
////    knobRight.write(0);
//  }
  counter ++;
}
