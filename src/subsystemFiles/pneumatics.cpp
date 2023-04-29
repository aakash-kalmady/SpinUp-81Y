#include "main.h"
using namespace pros;
bool angleShift_status = true;
bool intakeTension_status = true;
 
void expansionOP() {
  if (controller.get_digital(DIGITAL_X) == 1) {expand();}
} //end of expansion operator

void angleShifterOP() {
  if (controller.get_digital_new_press(DIGITAL_R1)) {
    if (angleShift_status == false) {angleShiftUp(), angleShift_status = true;}
    else {angleShiftDown(), angleShift_status = false;}
  } //end of if
} //end of angle shifter operator

void intakeTensionOP() {
  if (controller.get_digital_new_press(DIGITAL_DOWN)) {
    if (intakeTension_status == false) {intakeDown(), intakeTension_status = true;}
    else {intakeLift(), intakeTension_status = false;}
  } //end of if
} //end of angle shifter operator

void expand() {
  expansion.set_value(true);
} //end of expand far

void angleShiftUp() {
  angleShifter.set_value(true);
} //end of expand blocker

void angleShiftDown() {
  angleShifter.set_value(false);
} //end of expand blocker

void discTensionRelease() {
  discTension.set_value(false);
} //end of discTensionRelease

void discTensionEngage() {
  discTension.set_value(true);
} //end of discTensionEngage

void intakeLift() {
  intakeTension.set_value(true);
} //end of discTensionRelease

void intakeDown() {
  intakeTension.set_value(false);
} //end of discTensionEngage