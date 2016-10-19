//
// Created by matt on 19/10/16.
//

#include "../include/PositionTracker.h"

PositionTracker::PositionTracker(IMUPositionEstimater *imuPositionEstimater, ArucoPositioner *arucoPositioner) :
        imuPositionEstimater(imuPositionEstimater),
        arucoPositioner(arucoPositioner) {
    count = 0;
    xError, yError, zError = 0;
    imuPosX, imuPosY, imuPosZ = 0;
    imuLastX, imuLastY, imuLastZ = 0;
    arucoPosX, arucoPosY, arucoPosZ = 0;
}

bool PositionTracker::update() {
    bool updated = false;
    if (imuPositionEstimater->update()) {
        imuPosX = imuPositionEstimater->getXPos();
        imuPosY = imuPositionEstimater->getYPos();
        imuPosZ = imuPositionEstimater->getZPos();
        updated = true;
    }

    if (arucoPositioner->update()) {
        double newX = arucoPositioner->getPosX();
        double newY = arucoPositioner->getPosY();
        double newZ = arucoPositioner->getPosZ();

        ++count;
        xError += (newX - (arucoPosX + imuPosX));
        yError += (newY - (arucoPosY + imuPosY));
        zError += (newZ - (arucoPosZ + imuPosZ));

        arucoPosX = newX;
        arucoPosY = newY;
        arucoPosZ = newZ;

        imuLastX = imuPosX;
        imuLastY = imuPosY;
        imuLastZ = imuPosZ;

        updated = true;
    }

    return updated;
}

double PositionTracker::getPosX() {
    return (arucoPosX + imuPosX) - (xError / count);
}

double PositionTracker::getPosY() {
    return (arucoPosY + imuPosY) - (yError / count);
}

double PositionTracker::getPosZ() {
    return (arucoPosZ + imuPosZ) - (zError / count);
}