all: Main

HDRS = helper_3dmath.h I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h
CMN_OBJS = I2Cdev.o MPU6050.o
DMP_OBJS = Main.o Timer.o Stabiliser.o PWMDriver.o PIDController.o Motor.o IMU.o

# Set DMP FIFO rate to 20Hz when fifo rate is 9 to avoid overflows on 3d demo.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.
# fifo rate 1 = 100hz
CXXFLAGS = -std=c++14 -w -DDMP_FIFO_RATE=1 -Wall -g -O2 `pkg-config gtkmm-3.0 --cflags --libs`

$(CMN_OBJS) $(DMP_OBJS) : $(HDRS)


Main: $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -std=c++14 -o $@ $^ -lm

clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) Main