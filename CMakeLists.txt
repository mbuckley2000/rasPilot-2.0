cmake_minimum_required(VERSION 3.0)
project(rasPilot_2_0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -DDMP_FIFO_RATE=1 -Wall -g -O2")

set(SOURCE_FILES
        include/helper_3dmath.h
        src/I2Cdev.cpp
        include/I2Cdev.h
        src/IMU.cpp
        include/IMU.h
        src/Main.cpp
        src/Motor.cpp
        include/Motor.h
        src/MPU6050.cpp
        include/MPU6050.h
        include/MPU6050_6Axis_MotionApps20.h
        src/PIDController.cpp
        include/PIDController.h
        src/PWMDriver.cpp
        include/PWMDriver.h
        src/Stabiliser.cpp
        include/Stabiliser.h
        src/Timer.cpp
        include/Timer.h src/IMUPositionEstimater.cpp include/IMUPositionEstimater.h)

add_executable(rasPilot_2_0 ${SOURCE_FILES})