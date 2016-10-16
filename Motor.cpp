#include "Motor.h"

Motor::Motor(int gpioPin, int minPWM, int maxPWM) : driver(gpioPin), gpioPin(gpioPin), minPWM(minPWM), maxPWM(maxPWM) {
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
        driver.set((int) ((maxPWM - minPWM) * (throttle / 100)) + minPWM);
		return true;
	}
	return false;
}

bool Motor::initialise() {
	return setThrottle(100);
}
