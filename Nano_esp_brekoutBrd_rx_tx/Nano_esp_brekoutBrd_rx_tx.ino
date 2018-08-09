#include <SoftwareSerial.h>

SoftwareSerial esp8266(0,1);

//Stepper motor variables
int Steps = 4096; //4096 or 768
int cstep[2] = {0,0};

int s[][4] = {{8,9,10,11},{4,5,6,7}};

int m[] = {2,3};
bool dirs[]={true,true};

void reverseDirection(int num)
{
  //cstep[num]=0;
  //int i=num;
  for(int i=0;i<2;i++)
  {
    int a = s[num][i];
    s[num][i]= s[num][4-i-1];
    s[num][4-i-1] = a;    
  }
}


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


//Stepper moto setting
  //Serial.begin(9600);

  for(int i=0;i<4;i++)
  {
    pinMode(s[0][i],OUTPUT);
    pinMode(s[1][i],OUTPUT);
  }
  
  reverseDirection(1);
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

 /* 

  for(int i=0;i<2;i++)
  {
    bool mVal = digitalRead(m[i]);
    //Serial.print(mVal);
    if(dirs[i]!=mVal)
    {
      reverseDirection(i);
      dirs[i]=mVal;
    }  
  }
  Serial.println("");
 */ 
 // for(int x=0;x<Steps;x++)
  {
    if(cmd=="0")
     {
      //move LEFT 
      stepMove(0);// left wheels
      reverseDirection(1);
      stepMove(1);// both wheels
      reverseDirection(1);

     }
    if(cmd=="1")
     {
      //move RIGHT 
      stepMove(1);// right wheels
      reverseDirection(0);
      stepMove(0);// both wheels
      reverseDirection(0);

     }
     if(cmd=="2")
     {
      //move UP 
      
      stepMove(0);// both wheels
      stepMove(1);// both wheels
     }
     if(cmd=="3")
     {
      //move DOWN 
      reverseDirection(0);
      reverseDirection(1);
      stepMove(0);// both wheels
      stepMove(1);// both wheels
      reverseDirection(0);
      reverseDirection(1);
     }
  
     delayMicroseconds(900);
  }
 /*
  for(int x=0;x<Steps;x++)
  {  
    step1(2);    
    delayMicroseconds(900);
  }
  */
}



void stepMove(int num)
{
  //step
  int i = num;
  {
    switch(cstep[i])
    {
     case 0:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], HIGH);
     break; 
     case 1:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], HIGH);
     break; 
     case 2:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], LOW);
     break; 
     case 3:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], LOW);
     break; 
     case 4:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
     case 5:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
       case 6:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
     case 7:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], HIGH);
     break; 
     default:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
    }
  }
   
   cstep[i]=cstep[i]+1;
   if(cstep[i]==8)
     {cstep[i]=0;}
}








/*
void step1(int numOfSteppers)
{
  //stepp
  for(int i=0;i<numOfSteppers;i++)
  {
    switch(cstep)
    {
     case 0:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], HIGH);
     break; 
     case 1:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], HIGH);
     break; 
     case 2:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], LOW);
     break; 
     case 3:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], HIGH);
       digitalWrite(s[i][3], LOW);
     break; 
     case 4:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
     case 5:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], HIGH);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
       case 6:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
     case 7:
       digitalWrite(s[i][0], HIGH); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], HIGH);
     break; 
     default:
       digitalWrite(s[i][0], LOW); 
       digitalWrite(s[i][1], LOW);
       digitalWrite(s[i][2], LOW);
       digitalWrite(s[i][3], LOW);
     break; 
    }
  }
   
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
}

*/












