#include <unistd.h>
#include "../include/Motor.h"

Motor::Motor(PWMDriver *driver, int minPWM, int maxPWM) : driver(driver), minPWM(minPWM), maxPWM(maxPWM) {
    driver->initialise();
    driver->setRange(maxPWM);
}

Motor::~Motor() {}

double Motor::getThrottle() {
	return throttle;
}

bool Motor::setThrottle(double throttle) {
	if (throttle >= 0 && throttle <= 100) {
		this->throttle = throttle;
        driver->set((int) ((maxPWM - minPWM) * (throttle / 100)) + minPWM);
		return true;
	}
	return false;
}

/*
	void CalibrateMotors() {
		printf("\nEngine Calibration:\n");
		printf("    Setting to max PWM (Entering Calibration Mode)\n");
		SetMotor(-1, 2000);
		usleep(3000000);
		printf("    Setting Minimum Value\n");
		SetMotor(-1, MinPWM);
		usleep(1000000);
		SetMotor(-1, MinPWM);
		usleep(1000000);
		SetMotor(-1, MinPWM);
		usleep(1000000);
	}
 */

bool Motor::initialise() {
    setThrottle(100);
    usleep(500000);
    setThrottle(0);
    return true;
}
