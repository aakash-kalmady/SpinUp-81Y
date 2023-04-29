#include "main.h"
using namespace pros;

//HELPER FUNCTIONS
void setLift(int power) {
  lift = power;
}

//LIFT OPERATOR
void liftOP() {
  lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  int liftPower = 127 * (controller.get_digital(E_CONTROLLER_DIGITAL_R2) - controller.get_digital(E_CONTROLLER_DIGITAL_R1));
  setLift(liftPower);
} //end of lift operator
