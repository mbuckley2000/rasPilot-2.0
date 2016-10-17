#include "../include/PIDController.h"

PIDController::PIDController() {
	timer.start();
}

PIDController::~PIDController() {}

double PIDController::getCorrection() {
	double elapsedSeconds = timer.getElapsedSeconds();
	timer.start();
	double currentError = getCurrentError();
    double result = getPCorrection(currentError) + getICorrection(currentError, lastError, elapsedSeconds) +
                    getDCorrection(currentError, lastError, elapsedSeconds);
	lastError = currentError;
	return result;
}

void PIDController::setTarget(double target) {
	this->target = target;
}

void PIDController::setCurrent(double current) {
	this->current = current;
}

void PIDController::setPMultiplier(double pMult) {
	this->multiplier[0] = pMult;
}

void PIDController::setIMultiplier(double iMult) {
	this->multiplier[1] = iMult;
}

void PIDController::setDMultiplier(double dMult) {
	this->multiplier[2] = dMult;
}

double PIDController::getCurrentError() {
	return target - current;
}

double PIDController::getPCorrection(double currentError) {
	return multiplier[0] * currentError;
}

double PIDController::getICorrection(double currentError, double lastError, double elapsedSeconds) {
	lastICorrection += multiplier[1] * 0.5 * (currentError + lastError) * elapsedSeconds;
	return lastICorrection;
}

double PIDController::getDCorrection(double currentError, double lastError, double elapsedSeconds) {
	return multiplier[2] * (currentError - lastError) / elapsedSeconds;
}
