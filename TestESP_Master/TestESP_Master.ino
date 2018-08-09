#include <SoftwareSerial.h>

SoftwareSerial esp8266(8,9);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Started");

  // set the data rate for the SoftwareSerial port
  esp8266.begin(9600);
  esp8266.write("AT\r\n");
  
}

String ReadCommand()
{
    String str = esp8266.readStringUntil('\r');
    if(str.indexOf("GET /") >= 0)
    {
      int sPos = str.indexOf('/');
      int lPos = str.lastIndexOf(' ');
      str = str.substring(sPos,lPos);
      return str;
      //Serial.println(str);
    }
    return "";
}


void loop() {
  if (esp8266.available()) {

    String cmd = ReadCommand();
    if(cmd.length()>0)
    {
      // Got a command from the controller (i.e. HTTP page)
      Serial.println(cmd);      
    }
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}
