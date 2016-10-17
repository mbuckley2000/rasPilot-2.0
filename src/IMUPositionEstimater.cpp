//
// Created by matt on 17/10/16.
//

#include <iomanip>
#include "../include/IMUPositionEstimater.h"

IMUPositionEstimater::IMUPositionEstimater(IMU *imu) : imu(imu) {
    timer.start();
    velocity[0] = 0;
    velocity[1] = 0;
    velocity[2] = 0;
    position[0] = 0;
    position[1] = 0;
    position[2] = 0;
    acceleration[0] = 0;
    acceleration[1] = 0;
    acceleration[2] = 0;
    lastVelocity[0] = 0;
    lastVelocity[1] = 0;
    lastVelocity[2] = 0;
    lastAcceleration[0] = 0;
    lastAcceleration[1] = 0;
    lastAcceleration[2] = 0;
    accelTaken = false;
    velTaken = false;
}

void IMUPositionEstimater::update() {
    if (imu->hasNewData()) {
        getAcceleration();

        double elapsedTime = timer.getElapsedSeconds();
        timer.start();

        if (!accelTaken) {
            for (int i = 0; i < 3; i++) {
                lastAcceleration[i] = acceleration[i];
            }
            accelTaken = true;
        } else if (!velTaken) {
            for (int i = 0; i < 3; i++) {
                lastVelocity[i] = 0.5 * (acceleration[i] - lastAcceleration[i]) * elapsedTime;
            }
            velTaken = true;
        } else {
            for (int i = 0; i < 3; i++) {
                velocity[i] += 0.5 * (acceleration[i] - lastAcceleration[i]) * elapsedTime;
                position[i] += 0.5 * (velocity[i] - lastVelocity[i]) * elapsedTime;
                //std::cout << "Velocity: " << velocity[0] << ", " << velocity[1] << ", " << velocity[2] << std::endl;

                std::cout << "Position: " << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
                lastVelocity[i] = velocity[i];
                lastAcceleration[i] = acceleration[i];
            }
        }
    }
}

double IMUPositionEstimater::getXPos() {
    return position[0];    //std::cout << acceleration[0] << ", " << acceleration[1] << ", " << acceleration[2] << std::endl;

}

double IMUPositionEstimater::getYPos() {
    return position[1];
}

double IMUPositionEstimater::getZPos() {
    return position[2];
}

void IMUPositionEstimater::getAcceleration() {
    imu->getAcceleration(acceleration);
}
