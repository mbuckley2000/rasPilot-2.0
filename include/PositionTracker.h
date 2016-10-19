//
// Created by matt on 19/10/16.
//

#ifndef RASPILOT_2_0_POSITIONTRACKER_H
#define RASPILOT_2_0_POSITIONTRACKER_H

#include "IMUPositionEstimater.h"
#include "ArucoPositioner.h"

class PositionTracker {
public:
    PositionTracker(IMUPositionEstimater *imuPositionEstimater, ArucoPositioner *arucoPositioner);

    bool update();

    double getPosX();

    double getPosY();

    double getPosZ();

private:
    IMUPositionEstimater *imuPositionEstimater;
    ArucoPositioner *arucoPositioner;

    long long count;
    double xError, yError, zError;
    double imuPosX, imuPosY, imuPosZ;
    double imuLastX, imuLastY, imuLastZ;
    double arucoPosX, arucoPosY, arucoPosZ;
};

#endif //RASPILOT_2_0_POSITIONTRACKER_H