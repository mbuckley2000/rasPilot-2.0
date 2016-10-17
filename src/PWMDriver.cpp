#include "../include/PWMDriver.h"

PWMDriver::PWMDriver(int gpioPin, std::ofstream *pigpioDevice) :
		gpioPin(gpioPin),
		device(pigpioDevice) {}

PWMDriver::~PWMDriver() {}

bool PWMDriver::openDevice() {
	device->open("/dev/pigpio");
	return true;
}

bool PWMDriver::initialise() {
	//Set to write mode
	*device << "m " << gpioPin << "w" << "\n";
	*device << "w " << gpioPin << "0" << "\n";
	return true;
}

bool PWMDriver::startDaemon() {
	std::cout << "Starting pigpio daemon" << std::endl;
	//todo
	return true;
}

bool PWMDriver::setRange(int max) {
	rangeCap = max;
	*device << "PRS " << gpioPin << max << "\n";
	return true;
}

bool PWMDriver::set(int length) {
	if (!(length <= rangeCap && length >= 0)) return false;
	*device << "p " << gpioPin << " " << length << "\n";
	return true;
}