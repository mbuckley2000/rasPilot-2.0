#pragma once
#include "PWMDriver.h"
#include <stdlib.h>

/*
	A motor controller class.
	Controls an ESC (Electronic Speed Controller) using PWM through the Pi's GPIO
	Uses PIGPIO
*/
class Motor {
public:
	/*
		Constructor.
		gpioPin is the pin the ESC is connected to
		minPWM and maxPWM describe the range of PWM pulse lengths that the ESC takes
	*/
    Motor(PWMDriver *driver, int minPWM, int maxPWM);
	~Motor();

	/*
		Returns the current throttle % of the motor
	*/
	double getThrottle();

	/*
		Sets the motor's throttle %
		Returns true on success
	*/
	bool setThrottle(double throttle);

	/*
		Initialises the motor
		Programs the ESC with the PWM pulse range
	*/
	bool initialise();

private:
	double throttle;
    PWMDriver *driver;
	int maxPWM;
	int minPWM;
};