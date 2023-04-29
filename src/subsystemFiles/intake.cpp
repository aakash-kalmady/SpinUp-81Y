#include "main.h"
#include <string>
using namespace pros;
using namespace std;

void setIntake(int power) {
  intake = power;
} //end of setIntake

//INTAKE OPERATOR
void intakeOP() {
  int intakePower = (127 * (controller.get_digital(E_CONTROLLER_DIGITAL_L1)) - (127 * controller.get_digital(E_CONTROLLER_DIGITAL_L2)));
  setIntake(intakePower);
  if (controller.get_digital(E_CONTROLLER_DIGITAL_L2) == 1) {discTensionEngage();}
  else {discTensionRelease();}
} //end of intake operator

//ROLLS ROLLER DURING MATCH AUTON
void rollMatch(int maxTime) {
  intake.tare_position();
  bool rolled = false;
  int startTime = millis();
  while(!rolled) {
    setIntake(127);
    if (fabs(intake.get_position()) > 500) {rolled = true;}
    if (millis() - startTime > maxTime) {rolled = true;}
    delay(10);
  } //end of while
  setIntake(0);
  intake.tare_position();
} //end of rollMatch

//ROLLS ROLLER DURING SKILLS AUTON
void rollSkills(int maxTime) {
  intake.tare_position();
  bool rolled = false;
  int startTime = millis();
  while(!rolled) {
    setIntake(127);
    if (fabs(intake.get_position()) > 1200) {rolled = true;}
    if (millis() - startTime > maxTime) {rolled = true;}
    delay(10);
  } //end of while
  setIntake(0);
  intake.tare_position();
} //end of rollSkills