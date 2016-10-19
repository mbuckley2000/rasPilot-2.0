//
// Created by matt on 17/10/16.
//

#ifndef RASPILOT_2_0_IMUPOSITIONESTIMATER_H
#define RASPILOT_2_0_IMUPOSITIONESTIMATER_H

#include "Timer.h"
#include "IMU.h"

class IMUPositionEstimater {
public:
    IMUPositionEstimater(IMU *imu);

    bool update();

    double getXPos();

    double getYPos();

    double getZPos();

private:
    IMU *imu;
    Timer timer;
    double lastAcceleration[3];
    double lastVelocity[3];
    double acceleration[3];
    double velocity[3];
    double position[3];

    void getAcceleration();

    bool accelTaken;
    bool velTaken;
};


#endif //RASPILOT_2_0_IMUPOSITIONESTIMATER_H
