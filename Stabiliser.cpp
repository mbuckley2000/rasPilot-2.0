#include "Stabiliser.h"

Stabiliser::Stabiliser(int pitchPlusMotorPin, int pitchNegMotorPin, int rollPlusMotorPin, int rollNegMotorPin) :
		pitchPlusMotor(pitchPlusMotorPin, 0, 100),
		pitchNegMotor(pitchNegMotorPin, 0, 100),
		rollPlusMotor(rollPlusMotorPin, 0, 100),
		rollNegMotor(rollNegMotorPin, 0, 100) {}

Stabiliser::~Stabiliser() {}

bool Stabiliser::initialise() {
	//Initialise motors
	pitchPlusMotor.initialise();
	pitchNegMotor.initialise();
	rollPlusMotor.initialise();
	rollNegMotor.initialise();


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

		double yawCorrection = pidControllers[0].getCorrection() / 2;
		double pitchCorrection = pidControllers[1].getCorrection();
		double rollCorrection = pidControllers[2].getCorrection();

		rollPlusMotor.setThrottle(limitDouble(throttle + rollCorrection + yawCorrection, 0, 100));
		rollNegMotor.setThrottle(limitDouble(throttle - rollCorrection + yawCorrection, 0, 100));

		pitchPlusMotor.setThrottle(limitDouble(throttle + pitchCorrection - yawCorrection, 0, 100));
		pitchNegMotor.setThrottle(limitDouble(throttle - pitchCorrection - yawCorrection, 0, 100));
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
