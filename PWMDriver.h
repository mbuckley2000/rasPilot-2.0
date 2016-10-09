#pragma once
#include <iostream>
#include <fstream>

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
	PWMDriver();
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
		Starts the PIGPIO daemon
	*/
	bool startDaemon();

	/*
		Opens the PIGPIO device
	*/
	bool openDevice();

	/*
		Initialises the driver
	*/
	bool initialise();

private:
	int gpioPin;
	int rangeCap;
	static std::ofstream device;
};