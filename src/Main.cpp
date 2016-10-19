#include "../include/Stabiliser.h"
#include "../include/IMUPositionEstimater.h"
#include "../include/ArucoPositioner.h"
#include "../include/PositionTracker.h"

int main() {
    /*
     * PINS
     * WHITE BOTTOM 17
     * WHITE TOP 23
     * RED BOTTOM 15
     * RED TOP 8
     */
    PWMDriver pitchPlusDriver = PWMDriver(17);
    PWMDriver pitchNegDriver = PWMDriver(23);
    PWMDriver rollPlusDriver = PWMDriver(15);
    PWMDriver rollNegDriver = PWMDriver(8);

    std::vector<Motor *> motors;
    Motor pitchPlusMotor = Motor(&pitchPlusDriver, 0, 1500);
    Motor pitchNegMotor = Motor(&pitchNegDriver, 0, 1500);
    Motor rollPlusMotor = Motor(&rollPlusDriver, 0, 1500);
    Motor rollNegMotor = Motor(&rollNegDriver, 0, 1500);
    motors.push_back(&pitchPlusMotor);
    motors.push_back(&pitchNegMotor);
    motors.push_back(&rollPlusMotor);
    motors.push_back(&rollNegMotor);

    std::vector<PIDController *> pidControllers;
    PIDController yawController = PIDController();
    PIDController pitchController = PIDController();
    PIDController rollController = PIDController();
    pidControllers.push_back(&yawController);
    pidControllers.push_back(&pitchController);
    pidControllers.push_back(&rollController);

    IMU imu = IMU();

    Stabiliser stabiliser = Stabiliser(&imu, &pidControllers, &motors);

	stabiliser.initialise();
	stabiliser.setThrottle(2);

    IMUPositionEstimater positionEstimater = IMUPositionEstimater(&imu);

    raspicam::RaspiCam_Cv camera;
    aruco::CameraParameters camParam;
    ArucoPositioner arucoPositioner = ArucoPositioner(&camera, &camParam);
    arucoPositioner.initialise();

    PositionTracker positionTracker = PositionTracker(&positionEstimater, &arucoPositioner);

    while (true) {
        stabiliser.update();
        //positionEstimater.update();
        //arucoPositioner.update();
        if (positionTracker.update()) {
            //std::cout << "Pos: " << positionTracker.getPosX() << ", " << positionTracker.getPosY() << ", " << positionTracker.getPosZ() << std::endl;
        }
        //std::cout << "YPR: " << imu.getYaw() << ", " << imu.getPitch() << ", " << imu.getRoll() << std::endl;
    }

    return 0;
}