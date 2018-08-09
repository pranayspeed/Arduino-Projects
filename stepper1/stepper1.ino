#include <Stepper.h>

const int step =1;
Stepper s1(64,8,9,10,11);
void setup() {
  // put your setup code here, to run once:
  s1.setSpeed(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  s1.step(4096);
  //delay(900);
}
