int Steps = 4096; //4096 or 768
int cstep = 0;

int s[][4] = {{8,9,10,11},{4,5,6,7}};

int m[] = {2,3};
bool dirs[]={true,true};


void setup()
{
  Serial.begin(9600);

  for(int i=0;i<4;i++)
  {
    pinMode(s[0][i],OUTPUT);
    pinMode(s[1][i],OUTPUT);
  }
  //set pin 2,3 as input pins to change the direction of motors
  pinMode(m[0],INPUT);
  pinMode(m[1],INPUT);
}

void reverseDirection(int num)
{
  for(int i=0;i<2;i++)
  {
    int a = s[num][i];
    s[num][i]= s[num][4-i-1];
    s[num][4-i-1] = a;    
  }
}

void loop()
{

  for(int i=0;i<2;i++)
  {
    bool mVal = digitalRead(m[i]);
    Serial.print(mVal);
    if(dirs[i]!=mVal)
    {
      reverseDirection(i);
      dirs[i]=mVal;
    }  
  }
  Serial.println("");
 

  
  for(int x=0;x<Steps;x++)
  {
  
    step1(2);
    //delay(1);
    delayMicroseconds(900);
  }

  
}

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
