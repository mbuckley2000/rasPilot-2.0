#pragma once
#include "Timer.h"

/*
	PID controller class
	A proportional–integral–derivative controller (PID controller) is a control loop feedback mechanism (controller) commonly used in industrial control systems. (from wikipedia)
*/

class PIDController {
public:
	PIDController();
	~PIDController();

	/*
		Returns the correctional value that should be applied
	*/
	double getCorrection();

	/*
		Sets the target value
	*/
	void setTarget(double target);

	/*
		Sets the current value
	*/
	void setCurrent(double current);

	/*
		These three functions set the multipliers that control how much of each component makes up the overall correctional value
	*/
	void setPMultiplier(double pMult);
	void setIMultiplier(double iMult);
	void setDMultiplier(double dMult);

private:
	double multiplier[3];
	double target;
	double current;
	double lastICorrection;
	double lastError;
	double getCurrentError();
	double getPCorrection(double currentError);
	double getICorrection(double currentError, double lastError, double elapsedSeconds);
	double getDCorrection(double currentError, double lastError, double elapsedSeconds);
	Timer timer;
};

