#include "main.h"
using namespace pros;

bool clamp_status = true;

//CLAW OPERATOR
void clampOP() {
  if (controller.get_digital_new_press(DIGITAL_UP)) {
    if (clamp_status == false) {
      claw.set_value(true);
      clamp_status = true;
    } else {
      claw.set_value(false);
      clamp_status = false;
    }
  }
} //end of claw operator

//AUTONOMOUS FUNCTIONS
void clamp() {
  claw.set_value(false);
} //end of clamp

void releaseClamp() {
  claw.set_value(true);
} //end of release clamp
