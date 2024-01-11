#include "main.h"

void setIntake() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !shift()) {
    intakeMotor = 127;
    intakeLights.set_all(0x035e11);
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && shift()) {
    intakeMotor = -127;
    intakeLights.set_all(0x035e11);
  } else {
    intakeMotor = 0;
    intakeLights.set_all(0x000000);
  }
}