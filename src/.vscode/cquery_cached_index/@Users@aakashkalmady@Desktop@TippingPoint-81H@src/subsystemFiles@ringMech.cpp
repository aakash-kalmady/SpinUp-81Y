#include "main.h"
using namespace pros;

//HELPER FUNCTIONS
void setRingMech(int power) {
  ringMech = power;
}

bool ringMechF_status = false;
bool ringMechB_status = false;

//RINGMECH OPERATOR
void ringMechOP() {

  ringMech.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  if (controller.get_digital_new_press(DIGITAL_A)) {
    if (ringMechF_status == false) {
      setRingMech(0);
      ringMechF_status = true;
    } else {
      setRingMech(127);
      ringMechF_status = false;
    }
  }

  if (controller.get_digital_new_press(DIGITAL_B)) {
    if (ringMechB_status == false) {
      setRingMech(0);
      ringMechB_status = true;
    } else {
      setRingMech(-127);
      ringMechB_status = false;
    }
  }
} //end of ringmech operator
