#include "Stabiliser.h"

Stabiliser::Stabiliser(int pitchPlusMotorPin, int pitchNegMotorPin, int rollPlusMotorPin, int rollNegMotorPin) {
	this->motorGpioPins[0] = pitchPlusMotorPin;
	this->motorGpioPins[1] = pitchNegMotorPin;
	this->motorGpioPins[2] = rollPlusMotorPin;
	this->motorGpioPins[3] = rollNegMotorPin;
}

Stabiliser::~Stabiliser() {}

bool Stabiliser::initialise() {
	//Initialise motors
	for (int i = 0; i < 4; i++) {
		motors[i] = Motor(motorGpioPins[i], 0, 2000);
		motors[i].initialise();
	}
	
	//Set motor correction pairs
	//First index is the axis (YPR)
	//Second index is whether the motors are additive or subtractive
	//No yaw control as of yet
	axisMotorPairs[1][0].push_back(&motors[0]);
	axisMotorPairs[1][1].push_back(&motors[1]);
	axisMotorPairs[2][0].push_back(&motors[2]);
	axisMotorPairs[2][1].push_back(&motors[3]);


	//Initialise IMU
	imu = IMU();
	imu.initialise();

	//Initialise PID Controllers
	for (int i = 0; i < 3; i++) {
		pidControllers[i] = PIDController();
		pidControllers[i].setPMultiplier(0.5);
		pidControllers[i].setIMultiplier(0.2);
		pidControllers[i].setDMultiplier(0.1);
	}

	return true;
}

bool Stabiliser::update() {
	if (imu.read()) {
		//Read current orientation
		double ypr[3];
		ypr[0] = imu.getYaw();
		ypr[1] = imu.getPitch();
		ypr[2] = imu.getRoll();

		//Update PID controllers
		for (int i = 0; i < 3; i++) {
			pidControllers[i].setCurrent(ypr[i]);
			pidControllers[i].setTarget(0);
		}

		//Update motors
		for (int i = 0; i < 3; i++) {
			//Apply correction to the motor pairs
			double correction = pidControllers[i].getCorrection();
			//Add it to the positive motors
			for (Motor* motorPtr : axisMotorPairs[i][0]) {
				motorPtr->setThrottle(limitDouble(throttle + correction, 0, 100));
			}
			//Subtract it from the negative motors
			for (Motor* motorPtr : axisMotorPairs[i][1]) {
				motorPtr->setThrottle(limitDouble(throttle - correction, 0, 100));
			}
		}
		return true;
	}
	return false;
}

bool Stabiliser::setThrottle(double throttle) {
	this->throttle = throttle;
	return true;
}

double Stabiliser::getThrottle() {
	return throttle;
}

double Stabiliser::limitDouble(double value, double min, double max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}
