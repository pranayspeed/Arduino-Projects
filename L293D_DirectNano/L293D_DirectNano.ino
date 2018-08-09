
void setup() {
  //pinMode(5,OUTPUT);
 // pinMode(6,OUTPUT);
  }
void loop() {
  for(int i = 0; i<255; i++){
    digitalWrite(5, i);
    digitalWrite(6, 0);
    delay(5);
  }
  /*
  for(int i = 0; i<255; i++){
    analogWrite(5, i);
    analogWrite(6, 0);
    delay(5);
  }
  for(int i = 0; i<255; i++){
    analogWrite(5, 0);
    analogWrite(6, i);
    delay(5);
  }
  for(int i = 0; i<255; i++){
    analogWrite(5, 0);
    analogWrite(6, i);
    delay(5);
  }
  */
}
