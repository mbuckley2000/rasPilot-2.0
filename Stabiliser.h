#pragma once
#include "Motor.h"
#include "PIDController.h"
#include "IMU.h"
#include <vector>

/*
	Stabiliser class for the quadcopter
	Uses PID controllers to stabilise the quadcopter and change it's orientation
*/

class Stabiliser {
public:
	/*
		Constructor
		The pin numbers on the Raspberry Pi's GPIO
		pitchPlusMotorPin is the pin attached to the motor that would increase the pitch of the copter when turned on etc..
	*/
    Stabiliser(IMU *imu, std::vector<PIDController *> *pidControllers, std::vector<Motor *> *motors);
	~Stabiliser();

	/*
		Initialises the stabiliser
	*/
	bool initialise();

	/*
		Updates the motors
	*/
	bool update();

	/*
		Sets the desired throttle of the overall quadcopter
	*/
	bool setThrottle(double throttle);

	/*
		Gets the current throttle of the overall quadcopter
	*/
	double getThrottle();

private:
    std::vector<PIDController *> *pidControllers;
    std::vector<Motor *> *motors;
    IMU *imu;
	double throttle;
	double limitDouble(double value, double min, double max);
};