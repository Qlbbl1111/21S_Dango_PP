#include "main.h"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "autoSelect/selection.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 void motorTemp(){
  while(true) {
  float motorTemps = (left_front_motor.get_temperature()+left_back_motor.get_temperature() + right_front_motor.get_temperature()+right_back_motor.get_temperature())/4;
  //std::cout << motorTemps << std::endl;
  
  if (motorTemps <= 30) {
    controller.print(0, 0, "Drive: COLD, %.2f", motorTemps);
  } else if (motorTemps > 30 && motorTemps <= 45) {
    controller.print(0, 0, "Drive: WARM, %.2f", motorTemps);
  } else if (motorTemps > 45) {
    controller.print(0, 0, "Drive: HOT, %.2f", motorTemps);
  }
  pros::delay(2000);
  }
}

 void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    sylib::initialize();
    selector::init();

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
    pros::Task temps(motorTemp);
    	leftDriveLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
  	rightDriveLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
    intakeLights.set_all(0x000000);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
  left_front_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_back_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_top_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_top_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  switch (selector::auton) {
  case 1: //run auton for Blue WP
  break;
  case 2: //run auton for blue far 2 ball WP
  break;
  case 3: //run auton for blue far 4 ball
  break;
  case 4: //run auton for blue disrupt
  break;
  case 5: //run auton for blue nothing
  break;
  case 6: //run auton for blue nothing
  nothing();
  break;
  case -1: //run auton for Blue WP
  break;
  case -2: //run auton for blue far 2 ball WP
  break;
  case -3: //run auton for blue far 4 ball
  break;
  case -4: //run auton for blue disrupt
  break;
  case -5: //run auton for blue nothing
  break;
  case -6: //run auton for blue nothing
  nothing();
  break;
  case 0: //skills
  skills();
  break;
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  left_front_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_back_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_top_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_top_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  setDriveLights(0x0fdb35); //green
  bool last30 = false;
  std::uint32_t startTime = pros::millis();
  kickerRot.reset_position(); 
  while (true) {
    std::uint32_t time = pros::millis();

    driveControl(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    setKicker();
    setWings();
    setIntake();

    if (time-startTime >= 75000 && last30 != true) {
      leftDriveLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
      rightDriveLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
      controller.rumble(". . . . .");
      last30 = true;
    }

    pros::delay(10); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
