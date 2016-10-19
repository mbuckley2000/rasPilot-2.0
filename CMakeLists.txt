cmake_minimum_required(VERSION 3.0)
project(rasPilot_2_0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -DDMP_FIFO_RATE=1 -Wall -g -O2")

include_directories(/usr/local/include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

set(CMAKE_PREFIX_PATH /usr/local/lib)
find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED)
find_package(aruco REQUIRED)
find_package(pigpio REQUIRED)


set(SOURCE_FILES
        /usr/local/include/aruco/aruco.h
        /usr/local/include/pigpio.h
        /usr/local/include/opencv2/highgui/highgui.hpp
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
        include/Timer.h src/IMUPositionEstimater.cpp include/IMUPositionEstimater.h src/ArucoPositioner.cpp include/ArucoPositioner.h src/PositionTracker.cpp include/PositionTracker.h)

add_executable(Pilot ${SOURCE_FILES})
target_link_libraries(Pilot ${raspicam_CV_LIBS} aruco pigpio)
