#pragma once
#include <iostream>
#include <time.h>
#include <sys/time.h>

/*
	Basic timer class
	Use start to start and restart the timer
*/
class Timer {
public:
	Timer();
	~Timer();

	/*
		Starts the timer from 0
		Also restarts the timer
	*/
	void start();

	/*
		Gets elapsed seconds since start() was last called
	*/
	double getElapsedSeconds();

private:
	double getCurrentWorldTime();
	double startTime;
	struct timeval time;
};