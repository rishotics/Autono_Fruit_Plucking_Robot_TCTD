const int stepPin = 5; // CLK
const int dirPin = 2; //CW
const int enPin = 8; //EN
void setup() {
  
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  digitalWrite(dirPin,LOW); 
}
void loop() {
  
  // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  
  for(int x = 0; x < 20*16; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(800); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(800); 
  }

  delay(10000); // One second delay
 
}
