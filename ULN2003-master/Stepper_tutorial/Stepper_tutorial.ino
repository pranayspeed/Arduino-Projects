#include "ULN2003.h"

Stepmotor stepper1(4095, 4,5,6,7);
Stepmotor stepper2(4095, 8,9,10,11);

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  stepper1.setSpeed(17);
  stepper2.setSpeed(17);
}

// the loop routine runs over and over again forever:
void loop() {
  //stepper1.step(2048);
  //stepper2.step(2048);
  stepper1.revolution(-0.1);
  stepper2.revolution(0.1);
  //delay(1000);               // wait for a second
}
