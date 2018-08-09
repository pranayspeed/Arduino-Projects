/*
  ULN2003.h - Library for driving step motors sith the ULN2003 driver.
  Created by Charles Grassin, January 12, 2015.
  Released into the public domain.
*/
#ifndef ULN2003_h
#define ULN2003_h

#include "Arduino.h"

#define byte unsigned char

  class Stepmotor {
  public:
    Stepmotor(unsigned short int steps_per_revolution, byte IN1,byte IN2,byte IN3,byte IN4); //Constructor
    ~Stepmotor(); //Destructor
    void step(long int steps);
    void fullstep1phase(long int steps);
    void fullstep2phase(long int steps);
    void halfstep(long int steps);
    void fadeInStep(long int steps);
    void revolution(float revolutions);
    void setSpeed(float rpm);
    float getSpeed();
  private:
    void _setSpeedinus(unsigned short int delay);
    unsigned short int _revolution_delay;
    unsigned short int _steps_per_revolution;
    byte _IN1;
    byte _IN2;
    byte _IN3;
    byte _IN4;
  };

#endif