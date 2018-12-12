int ForUp = 3;
int BackUp = 4;
int ForSt = 5;
int BackSt =6;
void setup() {
  // put your setup code here, to run once:
pinMode (ForSt,OUTPUT);
pinMode (BackSt,OUTPUT);
pinMode (ForUp,OUTPUT);
pinMode (BackUp,OUTPUT);
}
void linearUP (int t)
{
  digitalWrite (ForSt,HIGH);
  digitalWrite (BackSt,LOW);
  
  digitalWrite (ForUp,LOW);
  digitalWrite (BackUp,HIGH);
  delay(t);
}
void linearUPStop ()
{
  digitalWrite (ForSt,LOW);
  digitalWrite (BackSt,LOW);
  
}
void loop() {
  // put your main code here, to run repeatedly:
linearUP(10000);
 
}
