#include "../include/Timer.h"

Timer::Timer() {}
Timer::~Timer() {}

void Timer::start() {
	startTime = getCurrentWorldTime();
}

double Timer::getElapsedSeconds() {
	return (getCurrentWorldTime() - startTime);
}

double Timer::getCurrentWorldTime() {
	if (gettimeofday(&time, NULL)) {
		std::cerr << "Unable to get current time" << std::endl;
	}
	return (double)time.tv_sec + (double)time.tv_usec * .000001;
}