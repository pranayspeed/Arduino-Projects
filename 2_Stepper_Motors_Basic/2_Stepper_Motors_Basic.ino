/*------------------------------------------------------
Two_Steppers.ino     Arduining.com  30 MAY 2015

Driving two steppers concurrently with the Arduino Nano.
stepperX follows potentiometer on analog input 0.
stepperY follows potentiometer on analog input 1.
A timeout is used to turn off coils and save energy in battery
operated applications.

Hardware:
Arduino NANO.
Drivers: ULN2003A
Stepper Motors: 28BYJ48, 5VDC, step angle 5.625 °
                Gear reduction 64:1
                No-load starting frequency:> = 500PPS (4 rpm)
                Coil resistance 60 Ohms.               
 -----------------------------------------------------*/

#include <Stepper.h>

#define  STEPSREV    4096    // 64(fullsteps) * 64 (reduction ratio)
#define  SPEED       4       // motor speed (RPM)

#define  COIL_1X     11
#define  COIL_2X     9
#define  COIL_3X     10
#define  COIL_4X     8

#define  COIL_1Y     7
#define  COIL_2Y     5
#define  COIL_3Y     6
#define  COIL_4Y     4

#define  POT_X       0
#define  POT_Y       1                
#define  TIMEOUT     1000    //Turns off after 1 sec of inactivity.
#define  NOISE       8       //inmunity in steps because analog noisy readings.

// create the instances of the stepper class.
Stepper stepperX(STEPSREV, COIL_1X, COIL_2X, COIL_3X, COIL_4X);
Stepper stepperY(STEPSREV, COIL_1Y, COIL_2Y, COIL_3Y, COIL_4Y);

int potValX,potValY;           // potentiometers analog readings
int Xpos,Ypos;                 // Actual steppers positions(0-4096)->(0-360°)
int newXpos, newYpos;          // New steppers positions
unsigned long stampX, stampY;  // last move time stamped.

//============== functions ====================================================

//Read the potentiometers and map the reading to mach 360 degrees.
void readPots(){
  potValX = analogRead(POT_X);          // read POT_X value (0-1023).
  potValY = analogRead(POT_Y);          // read POT_Y value (0-1023).
  newXpos= map(potValX,0,1023,0,2047);  // Map pot X range to one stepper turn.
  newYpos= map(potValY,0,1023,0,2047);  // Map pot Y range to the stepper turn.
}
 
//-----------------------------------------------------------------------------
// Aproach stepperX to the newX position.
void aproachX(int newX){
  int Xdir = Xpos<newX ? 1 : -1;
  stepperX.step(Xdir);        // move one step in the Xdir direction.
  Xpos += Xdir;               // update Xpos.
  stampX = millis();          // stamp actual time.
  }

//-----------------------------------------------------------------------------
// Aproach stepperY to the newY position.
void aproachY(int newY){
  int Ydir = Ypos<newY ? 1 : -1;
  stepperY.step(Ydir);        // move one step in the Ydir direction.
  Ypos += Ydir;               // update Ypos.
  stampY = millis();          // stamp actual time.
  }

//-----------------------------------------------------------------------------
//Check for inactivity and turn off the steppers coils to save battery.
void CheckTimeout(){
  if((millis() - stampX) > TIMEOUT){   //Turn Off StepperX coils.
    digitalWrite(COIL_1X, LOW);
    digitalWrite(COIL_2X, LOW);
    digitalWrite(COIL_3X, LOW);
    digitalWrite(COIL_4X, LOW);
  }
  if((millis() - stampY) > TIMEOUT){   //Turn Off StepperY coils.
    digitalWrite(COIL_1Y, LOW);
    digitalWrite(COIL_2Y, LOW);
    digitalWrite(COIL_3Y, LOW);
    digitalWrite(COIL_4Y, LOW);
  }    
}


//=================== setup ===================================================
void setup(){
  stepperX.setSpeed(SPEED);  // set the X motor speed.
  stepperY.setSpeed(SPEED);  // set the Y motor speed.
  readPots();
  Xpos = newXpos;
  Ypos = newYpos;
}

//================= main loop =================================================
void loop(){
  readPots();
//if diference is greater than NOISE move steppers.
  if(abs(newXpos - Xpos)> NOISE) aproachX(newXpos);
  if(abs(newYpos - Ypos)> NOISE) aproachY(newYpos);

  CheckTimeout();   //check for inactivity.

}

