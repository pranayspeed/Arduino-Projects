#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor m1(1),m2(2),m3(3),m4(4);

SoftwareSerial esp8266(0,1);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Started");

  // set the data rate for the SoftwareSerial port
  esp8266.begin(9600);
  esp8266.write("AT\r\n");

    Serial.println("Motor test!");

  // turn on motor
  m1.setSpeed(200);
  m2.setSpeed(200);
  m3.setSpeed(200);
  m4.setSpeed(200);
 
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}

String ReadCommand()
{
    String str = esp8266.readStringUntil('\r');
    if(str.indexOf("GET /") >= 0)
    {
      int sPos = str.indexOf('/');
      int lPos = str.lastIndexOf(' ');
      str = str.substring(sPos,lPos);
      sPos = str.indexOf('=');
      str = str.substring(sPos+1);
      return str;
      //Serial.println(str);
    }
    return "";
}

String cmd="-1";
void loop() {
  if (esp8266.available()) {
    //Serial.println(esp8266.readString());
    
    String cmdtmp = ReadCommand();
    if(cmdtmp.length()>0)
    {
      // Got a command from the controller (i.e. HTTP page)
      cmd=cmdtmp;
      Serial.println(cmd);      
     
    }
    
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }

    {
    if(cmd=="0")
     {
      //move LEFT 
        m1.run(FORWARD);
        m2.run(FORWARD);
        m3.run(BACKWARD);
        m4.run(BACKWARD);
      

     }
    if(cmd=="1")
     {
      //move RIGHT 
        m3.run(FORWARD);
        m4.run(FORWARD);
        m1.run(BACKWARD);
        m2.run(BACKWARD);
      

     }
     if(cmd=="2")
     {
      //move UP 
        m1.run(FORWARD);
        m2.run(FORWARD);
        m3.run(FORWARD);
        m4.run(FORWARD);
      

     }
     if(cmd=="3")
     {
      //move DOWN 
        m1.run(BACKWARD);
        m2.run(BACKWARD);
        m3.run(BACKWARD);
        m4.run(BACKWARD);
      

     } 
  }
}
