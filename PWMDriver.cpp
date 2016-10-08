#include "PWMDriver.h"
PWMDriver::PWMDriver(int gpioPin) {
	PWMDriver::gpioPin = gpioPin;
}

PWMDriver::~PWMDriver() {}

bool PWMDriver::openDevice() {
	device.open("/dev/pigpio");
}

bool PWMDriver::initialise() {
	//Set to write mode
	device << "m " << gpioPin << "w" << "\n";
	device << "w " << gpioPin << "0" << "\n";
}

bool PWMDriver::startDaemon() {
	std::cout << "Starting pigpio daemon" << std::endl;
}

bool PWMDriver::setRange(int max) {
	rangeCap = max;
	device << "PRS " << gpioPin << max << "\n";
}

bool PWMDriver::set(int length) {
	if (!(length <= rangeCap && length >= 0)) return false;
	device << "p " << gpioPin << " " << length << "\n";
}