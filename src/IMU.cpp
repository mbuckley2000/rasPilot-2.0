#include "../include/IMU.h"
#include <iostream>

#define PI 3.14159265359

IMU::IMU() {
	newDataAvailable = false;
}

IMU::~IMU() {}

bool IMU::initialise() {
	std::cout << "MPU6050 Sensor Initialization:" << std::endl;
	// initialize device
	std::cout << "Initializing I2C devices" << std::endl;
	mpu.initialize();

	// verify connection
	std::cout << "Testing device connections" << std::endl;
	printf(mpu.testConnection() ? "    MPU6050 connection successful\n" : "    MPU6050 connection failed\n");

	// load and configure the DMP
	printf("    Initializing DMP...\n");
	devStatus = mpu.dmpInitialize();

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		printf("    Enabling DMP...\n");
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		//Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		//attachInterrupt(0, dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		printf("    DMP ready!\n");
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
		return true;
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		printf("    DMP Initialization failed (code %d)\n", devStatus);
	}
	return false;
}

bool IMU::read() {
	if (!dmpReady) return false;

	fifoCount = mpu.getFIFOCount(); // get current FIFO count

	if (fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		printf("FIFO overflow! Resetting FIFO\n");
	} else if (fifoCount >= 42) {  // otherwise, check for DMP data ready interrupt (this should happen frequently)
		mpu.getFIFOBytes(fifoBuffer, (uint8_t) packetSize); // read a packet from FIFO
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

		acceleration[0] = mpu.getAccelerationX();
		acceleration[1] = mpu.getAccelerationY();
		acceleration[2] = mpu.getAccelerationZ();

		//printf("Current orientation:\n\tYAW:%.2f\tPITCH:%.2f\tROLL:%.2f\n\n", CurrentAngle[0], CurrentAngle[1], CurrentAngle[2]);

		newDataAvailable = true;
		return(true); //Only case of 0 return is if motors are updated
	}
	return false;
}

double IMU::getYaw() {
	return ypr[0] * 180 / PI;;
}

double IMU::getPitch() {
	return ypr[1] * 180 / PI;;
}

double IMU::getRoll() {
	return ypr[2] * 180 / PI;;
}

void IMU::getAcceleration(double *vec) {
	newDataAvailable = false;
	vec[0] = acceleration[0];
	vec[1] = acceleration[1];
	vec[2] = acceleration[2];
}

bool IMU::hasNewData() {
	return newDataAvailable;
}
