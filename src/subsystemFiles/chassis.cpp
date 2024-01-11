#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "pros/motors.h"

int curve(int input) {
    double t = 7;
    return (exp(-(t/10))+exp((abs(input)-127)/10)*(1- exp(-(t/10))))*input;
}

void reset_drive_sensor(){
    left_front_motor.tare_position();
    right_front_motor.tare_position();  
}
void set_tank(int left, int right) {
    left_side_motors = left;
    right_side_motors = right;
}

float active_brake_kp = 2;
void driveControl(int l_stick, int r_stick) {
        //left side
        if (abs(l_stick) > 5) { // Threshold if joysticks don't come back to perfect 0
            left_side_motors = curve(l_stick);
            if (active_brake_kp != 0) left_front_motor.tare_position();
        }
        //When joys are released, run active brake (P) on drive left
        else {
            left_side_motors = (0 - left_front_motor.get_position()) * active_brake_kp;
        }
        //right side
        if (abs(r_stick) > 5) { // Threshold if joysticks don't come back to perfect 0
            right_side_motors = curve(r_stick); 
            if (active_brake_kp != 0) right_front_motor.tare_position(); 
        }
        //When joys are released, run active brake (P) on drive right
        else {
            right_side_motors = (0 - right_front_motor.get_position()) * active_brake_kp;
        }
}

lemlib::Drivetrain drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    10.5, // track width
    lemlib::Omniwheel::NEW_275, // wheel diameter
    450, // wheel rpm
    2
};

// odometry struct
lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial // inertial sensor
};
 
// forward/backward PID
lemlib::ControllerSettings lateralController (
    10, // kP
    0, //kI
    3, // kD
    3, //anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    20 // slew rate
);
 
// turning PID
lemlib::ControllerSettings angularController (
    2, // kP
    0, //kI
    10, // kD
    3, //anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
);
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);