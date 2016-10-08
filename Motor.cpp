#include "Motor.h"
#include <unistd.h>

Motor::Motor(int gpioPin, int minPWM, int maxPWM) {
	this->gpioPin = gpioPin;
	this->minPWM = minPWM;
	this->maxPWM = maxPWM;
	driver = PWMDriver(gpioPin);
	driver.initialise();
	driver.setRange(maxPWM);
}

Motor::~Motor() {}

double Motor::getThrottle() {
	return throttle;
}

bool Motor::setThrottle(double throttle) {
	if (throttle >= 0 && throttle <= 100) {
		this->throttle = throttle;
		driver.set(((maxPWM - minPWM) * (throttle/100)) + minPWM);
		return true;
	}
	return false;
}

bool Motor::initialise() {
	setThrottle(100);
	usleep(3000000);
}
