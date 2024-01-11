#include "main.h"

okapi::ControllerButton cataHold(okapi::ControllerDigital::L2);

bool toggleKicker = false;
bool latchKicker = false;

void setKickerMotors(int value) {
  kicker_a = value;
  kicker_b = value; 
}
bool kickerDown2 = false;
void setKicker() {
  kicker_a.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  kicker_b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  /*
  //Cata Toggle (L2 Button)
  if (cataHold.isPressed()) {
    if (!latchKicker) { // if latch false, toggle one time and set latch true
      toggleKicker = !toggleKicker;
      latchKicker = true;
    }
  } else {
    latchKicker = false; // once button is released then release the latch too
  }
  */

  //Cata Control (L1 for press, L2 for Toggle)
  if (toggleKicker ^ controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ) {
    //set motors for toggle or press but Dont allow toggle and press
    setKickerMotors(127);
    //kickerDown2 = false;

  } else {
    //turn off if neither
    setKickerMotors(0);
      /*
      if (!kickerLimit.get_value() && !kickerDown2) {
        setKickerMotors(127);
      } else {
      kickerDown2 = true;
      setKickerMotors(0);
  }
  */
  }

}
  //Over Draw Protection
  //std::cout << "Motor Current Draw: " << cata_a.get_current_draw();
  //if (cata_a.get_current_draw() > 1550) {
   //   stopKicker = true;
   // } 