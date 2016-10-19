#include "../include/PWMDriver.h"

PWMDriver::PWMDriver(int gpioPin) :
        gpioPin(gpioPin) {}

PWMDriver::~PWMDriver() {
    gpioTerminate();
}

bool PWMDriver::initialise() {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio initialisation failed\n");
        return false;
    }

    gpioSetMode(gpioPin, PI_OUTPUT);
    return true;
}

bool PWMDriver::setRange(int max) {
	rangeCap = max;
    //TODO
	return true;
}

bool PWMDriver::set(int length) {
	if (!(length <= rangeCap && length >= 0)) return false;
    gpioServo(gpioPin, length);
    return true;
}