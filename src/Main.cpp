#include "../include/Stabiliser.h"
#include "../include/IMUPositionEstimater.h"

int main() {
    std::ofstream pigpioDevice;
    pigpioDevice.open("/dev/pigpio");

    PWMDriver pitchPlusDriver = PWMDriver(10, &pigpioDevice);
    PWMDriver pitchNegDriver = PWMDriver(15, &pigpioDevice);
    PWMDriver rollPlusDriver = PWMDriver(25, &pigpioDevice);
    PWMDriver rollNegDriver = PWMDriver(23, &pigpioDevice);

    std::vector<Motor *> motors;
    Motor pitchPlusMotor = Motor(&pitchPlusDriver, 0, 100);
    Motor pitchNegMotor = Motor(&pitchNegDriver, 0, 100);
    Motor rollPlusMotor = Motor(&rollPlusDriver, 0, 100);
    Motor rollNegMotor = Motor(&rollNegDriver, 0, 100);
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

    while (true) {
        stabiliser.update();
        positionEstimater.update();
        //std::cout << "YPR: " << imu.getYaw() << ", " << imu.getPitch() << ", " << imu.getRoll() << std::endl;
    }

    return 0;
}