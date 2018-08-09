#include "Arduino.h"
#include "ULN2003.h"

// Define the RPM used by default if an invalid RPM is sent.
#define DEFAULT_RPM 10

// Initialize requiered varible for the library. Should be called once when the stepper is declared.
Stepmotor::Stepmotor(unsigned short int steps_per_revolution, byte IN1, byte IN2, byte IN3, byte IN4)
{
	//Delay between each steps. When increased, the torque increases (theoritically), but the rpm decreases. Should not be >16 (to be tested).
	_revolution_delay = 2000;
	//Number of steps to complete one revolution. Should be 4096.
	_steps_per_revolution = steps_per_revolution;
	//Arduino Pins :
	_IN1 = IN1;
	_IN2 = IN2;
	_IN3 = IN3;
	_IN4 = IN4;
	//Set all the pins to OUTPUT
	pinMode(IN1, OUTPUT); 
	pinMode(IN2, OUTPUT); 
	pinMode(IN3, OUTPUT); 
	pinMode(IN4, OUTPUT);
}

// Destructor
Stepmotor::~Stepmotor()
{/*nothing to destruct*/}

//Turn the stepper from the provided amount of steps. Negative = Counter Clockwise, Positive = Clockwise.
//It is the function you should use if you are new to stepper motors
void Stepmotor::step(long int steps)
{
	halfstep(steps);
}

// @FixMe : rpm doesn't match reality in this mode
/// Mode One-Phase On, full step ///
/* This mode should have a low torque, but use a lot less energy.
   The coils are powered according to the following table :

   |-------------------------|
   | Coils : | A | B | C | D |
   |---------|---|---|---|---|
   | Step 1  | 1 | 0 | 0 | 0 |
   | Step 2  | 0 | 1 | 0 | 0 |
   | Step 3  | 0 | 0 | 1 | 0 |
   | Step 4  | 0 | 0 | 0 | 1 |
   |-------------------------|

   NB : '1' means that the coil is powered, and '0' that it is connected to GND.
   NB 2 : In case of an interupted usage, your steps should be a multiple of 4.
 */
void Stepmotor::fullstep1phase(long int steps)
{
	int stage = 0;
	while (steps != 0)
	{
		switch(stage){
			case 0:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 1:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 2:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, LOW);
			break; 
			case 3:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, HIGH);
			break; 
			default:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
		}
		if(steps > 0) {
			stage--; steps --;
			if(stage<0){stage=3;}
		}
		else if (steps < 0) {
			stage ++; steps ++;
			if(stage>3){stage=0;} 
		}
		delayMicroseconds(_revolution_delay);	
	}
}

// @FixMe : rpm doesn't match reality in this mode
/// Mode Two-Phase On, full step ///
/* This mode should have a high torque, but use a lot of energy.
   The coils are powered according to the following table :

   |-------------------------|
   | Coils : | A | B | C | D |
   |---------|---|---|---|---|
   | Step 1  | 1 | 1 | 0 | 0 |
   | Step 2  | 0 | 1 | 1 | 0 |
   | Step 3  | 0 | 0 | 1 | 1 |
   | Step 4  | 1 | 0 | 0 | 1 |
   |-------------------------|

   NB : '1' means that the coil is powered, and '0' that it is connected to GND.
   NB 2 : In case of an interupted usage, your steps should be a multiple of 4.
 */
void Stepmotor::fullstep2phase(long int steps)
{
	int stage = 0;
	while (steps != 0)
	{
		switch(stage){
			case 0:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 1:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, LOW);
			break; 
			case 2:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, HIGH);
			break; 
			case 3:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, HIGH);
			break; 
			default:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
		}
		if(steps > 0) {
			stage--; steps --;
			if(stage<0){stage=3;}
		}
		else if (steps < 0) {
			stage ++; steps ++;
			if(stage>3){stage=0;} 
		}
		delayMicroseconds(_revolution_delay);	
	}
}

/// Mode Half-step ///
/* This mode should have a medium torque, and use medium level of energy.
   It alows the precision to be twice as high as the other two modes.
   The coils are powered according to the following table :

   |-------------------------|
   | Coils : | A | B | C | D |
   |---------|---|---|---|---|
   | Step 1  | 1 | 0 | 0 | 0 |
   | Step 2  | 1 | 1 | 0 | 0 |
   | Step 3  | 0 | 1 | 0 | 0 |
   | Step 4  | 0 | 1 | 1 | 0 |
   | Step 5  | 0 | 0 | 1 | 0 |
   | Step 6  | 0 | 0 | 1 | 1 |
   | Step 7  | 0 | 0 | 0 | 1 |
   | Step 8  | 1 | 0 | 0 | 1 |
   |-------------------------|

   NB : '1' means that the coil is powered, and '0' that it is connected to GND.
   NB 2 : In case of an interupted usage, your steps should be a multiple of 8.
 */
void Stepmotor::halfstep(long int steps)
{
	int stage = 0;
	while (steps != 0)
	{
		switch(stage){
			case 0:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, HIGH);
			break; 
			case 1:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, HIGH);
			break; 
			case 2:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, LOW);
			break; 
			case 3:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, HIGH);
			digitalWrite(_IN4, LOW);
			break; 
			case 4:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 5:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, HIGH);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 6:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
			case 7:
			digitalWrite(_IN1, HIGH); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, HIGH);
			break; 
			default:
			digitalWrite(_IN1, LOW); 
			digitalWrite(_IN2, LOW);
			digitalWrite(_IN3, LOW);
			digitalWrite(_IN4, LOW);
			break; 
		}
		if(steps > 0) {
			stage--; steps --;
			if(stage<0){stage=7;}
		}
		else if (steps < 0) {
			stage ++; steps ++;
			if(stage>7){stage=0;} 
		}
		delayMicroseconds(_revolution_delay);	
	}
}


void Stepmotor::fadeInStep(long int steps)
{
	unsigned short int temp = _revolution_delay;
	_setSpeedinus(2*_revolution_delay);
	while(_revolution_delay > temp && steps != 0)
	{
		if (steps >= 10) {
			step(10);
			steps -= 10;
		}
		else if (steps <= -10)
		{
			step(-10);
			steps += 10;
		}
		else
		{
			step(steps);
			steps = 0;
		}
		_setSpeedinus(_revolution_delay - (float)1/25*temp);
	}
	_setSpeedinus(temp);step(steps);
}

//Turn the stepper from the provided amount of full revolutions. Negative = Counter Clockwise, Positive = Clockwise.
void Stepmotor::revolution(float revolutions)
{
	step(revolutions * _steps_per_revolution);
}

//Change the rotation speed of the stepper. Can be called at any time. rpm should be <16 (test with your own motor)
void Stepmotor::setSpeed(float rpm)
{
	if(rpm < 0) {rpm = DEFAULT_RPM;}
	_revolution_delay = 60*1000000/(long)(rpm*(long)_steps_per_revolution);
}

//Return the currend speed value in rpm
float Stepmotor::getSpeed()
{
	return 60*1000000/((long)_revolution_delay*_steps_per_revolution);
}

void Stepmotor::_setSpeedinus(unsigned short int delay)
{
	_revolution_delay = delay;
}