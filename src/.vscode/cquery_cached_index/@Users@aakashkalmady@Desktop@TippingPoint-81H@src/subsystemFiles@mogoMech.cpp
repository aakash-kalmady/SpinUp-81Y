#include "main.h"
using namespace pros;

bool mogo_status = true;
//HELPER FUNCTIONS
void mogoMechOP() {
    if (controller.get_digital_new_press(DIGITAL_X)) {
      if (mogo_status == false) {
        mogoMech.set_value(true);
        mogo_status = true;
      } else {
        mogoMech.set_value(false);
        mogo_status = false;
      }
    }
} //end of mogoMech operator

//AUTONOMOUS FUNCTIONS
void clampMogo() {
  mogoMech.set_value(true);
}

void releaseMogo() {
  mogoMech.set_value(false);
}
