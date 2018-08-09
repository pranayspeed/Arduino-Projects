#include <ESP8266Scheduler.h>

void serialLoop() {
  int num = 0;
  while (true) {
    Serial.printf("The number is %d\n", num++);
    delay(1000);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Scheduler.startLoop(serialLoop);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
