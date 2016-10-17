#include "../include/Stabiliser.h"

Stabiliser::Stabiliser(IMU *imu, std::vector<PIDController *> *pidControllers, std::vector<Motor *> *motors) :
		imu(imu),
		pidControllers(pidControllers),
		motors(motors) {}

Stabiliser::~Stabiliser() {}

bool Stabiliser::initialise() {
	//Initialise motors
	for (Motor *motor : *motors) {
		motor->initialise();
	}

	//Initialise IMU
	imu->initialise();

	//Initialise PID Controllers
	for (int i = 0; i < 3; i++) {
		(*pidControllers)[i]->setPMultiplier(0.5);
		(*pidControllers)[i]->setIMultiplier(0.2);
		(*pidControllers)[i]->setDMultiplier(0.1);
	}

	return true;
}

bool Stabiliser::update() {
	if (imu->read()) {
		//Read current orientation
		double ypr[3];
		ypr[0] = imu->getYaw();
		ypr[1] = imu->getPitch();
		ypr[2] = imu->getRoll();

		//Update PID controllers
		for (int i = 0; i < 3; i++) {
			(*pidControllers)[i]->setCurrent(ypr[i]);
			(*pidControllers)[i]->setTarget(0);
		}

		double yawCorrection = (*pidControllers)[0]->getCorrection() / 2;
		double pitchCorrection = (*pidControllers)[1]->getCorrection();
		double rollCorrection = (*pidControllers)[2]->getCorrection();

		(*motors)[2]->setThrottle(limitDouble(throttle + rollCorrection + yawCorrection, 0, 100));
		(*motors)[3]->setThrottle(limitDouble(throttle - rollCorrection + yawCorrection, 0, 100));

		(*motors)[0]->setThrottle(limitDouble(throttle + pitchCorrection - yawCorrection, 0, 100));
		(*motors)[1]->setThrottle(limitDouble(throttle - pitchCorrection - yawCorrection, 0, 100));
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
