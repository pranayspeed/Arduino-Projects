#include<Servo.h>

Servo servo;


void setup() {
  // put your setup code here, to run once:
  servo.attach(8);
  servo.write(0);
  delay(2000);

}
int i=0;
void loop() {
  // put your main code here, to run repeatedly:

  
  servo.write(300);
 // i=(i+5)%360;
  //delay(1000);
 // servo.write(0);
  delay(1000);
  
}
