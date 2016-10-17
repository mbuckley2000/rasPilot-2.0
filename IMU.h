#pragma once
#include <stdint.h>
#include "MPU6050_6Axis_MotionApps20.h"
/*
	Wrapper class for the open source MPU9250 library
*/

class IMU {
public:
	IMU();
	~IMU();
	/*
		Initialises the sensor.
		Returns true on success.
	*/
	bool initialise();

	/*
		Reads orientation data from the DMP chip on the sensor.
		Use getYaw(), getPitch(), and getRoll() to retreive the values.
		Returns true on success.
	*/
	bool read();

	/*
		These three functions retreive the read values from read()
	*/
	double getYaw();
	double getPitch();
	double getRoll();

    bool hasNewData();

    void getAcceleration(double *vec);


private:
	// IMU Variables
	// class default I2C address is 0x68
	// specific I2C addresses may be passed as a parameter here
	// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
	// AD0 high = 0x69
	MPU6050 mpu;

	// MPU control/status vars
	bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

							// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorInt16 aa;         // [x, y, z]            accel sensor measurements
	VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
	VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float euler[3];         // [psi, theta, phi]    Euler angle container
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    bool newDataAvailable;

    double acceleration[3];
};