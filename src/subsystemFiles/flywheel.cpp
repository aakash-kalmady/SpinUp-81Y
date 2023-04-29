#include "main.h"
#include <string>
using namespace pros;
using namespace std;
using namespace lcd;
const int closeShootingRPM = 2620;
bool rpm_status = false, shooting;
int threshold, targetRPM;

void setFlywheel(int power) {
  flywheel = power;
} //end of setFlywheel

int shotTrackerValue() {
  return shotTracker.get_value();
} //end of shotTrackerValue

void shoot() {
  int lineSensorShotThreshold = 2875;
  shooting = true;
  bool is_shot = false;
  int startTime = millis();
  while (!is_shot) {
    setIntake(-127);
    if (shotTrackerValue() < lineSensorShotThreshold) {is_shot = true;}
    if (millis() - startTime > 650) {is_shot = true;}
    delay(10);
  } //end of while
  setIntake(127);
  delay(20);
  setIntake(0);
  shooting = false;
} //end of shoot

void farMode(int target) {
  targetRPM = target;
  threshold = 100;
} //end of farMode

void closeMode() {
  targetRPM = closeShootingRPM;
  threshold = 200;
} //end of closeMode

void middleMode(int target) {
  targetRPM = target;
  threshold = 150;
} //end of closeMode

float kP = 0.15, kV = .0353, error; int output = 0;
string displayRPM;
void flywheelOP() {
  while (true) {
    if (controller.get_digital_new_press(DIGITAL_R1)) {
      if (rpm_status == false) {middleMode(2850), angleShiftDown(), rpm_status = true;}
      else {closeMode(), angleShiftUp(), rpm_status = false;}
    } //end of if
    //P term, proportional to the error
    error = targetRPM - flywheel.get_actual_velocity() * 6;
    //bang-bang controller
    if (error > threshold) {output = 127;}
    if (shooting) {output = 127;}
    else if (error < -threshold) {output = 0;}
    //feedforward + P controller
    else {output = (kV * targetRPM) + (kP * error);}
    //controls flywheel output
    if(output > 127) {output = 127;}
    else if(output < 0) {output = 0;}
    setFlywheel(output);
    if (controller.get_digital(E_CONTROLLER_DIGITAL_L2) == 1) {setFlywheel(127);}
    displayRPM = to_string(flywheel.get_actual_velocity() * 6);
    set_text(5, "Flywheel RPM: " + displayRPM);
    delay(10);
  } //end of while
} //end of flywheelOP
