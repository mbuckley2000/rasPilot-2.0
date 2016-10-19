#pragma once
#include <iostream>
#include <pigpio.h>

/*
	PWM driver class for controlling PWM devices over the Raspberry Pi's GPIO
*/

class PWMDriver {
public:
	/*
		Constructor
		gpioPin is the pin that the PWM device is connected to
	*/
    PWMDriver(int gpioPin);
	~PWMDriver();

	/*
		Sets the maximum length of PWM pulse
	*/
	bool setRange(int max);

	/*
		Sets the current length of PWM pulse
	*/
	bool set(int length);

	/*
		Initialises the driver
	*/
	bool initialise();

private:
	int gpioPin;
	int rangeCap;
};