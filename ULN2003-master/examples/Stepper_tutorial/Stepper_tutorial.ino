#include "ULN2003.h"

Stepmotor stepper(4095, 4,5,6,7);

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  stepper.setSpeed(17);
}

// the loop routine runs over and over again forever:
void loop() {
  stepper.step(3000);
  //stepper.revolution(-1);
  delay(1000);               // wait for a second
}
