#include "main.h"
#include <string>
using namespace pros;
using namespace std;

void autonHandler(int auton) {
  switch (auton) {
  case 0:
    experimental(); // experimental autonomous
    break;
  case 1:
    leftWP(); // left win point autonomous
    break;
  case 2:
    leftRisk(); // left risk autonomous
    break;
  case 3:
    left(); // left autonomous
    break;
  case 4:
    rightRisk(); // right risk autonomous
    break;
  case 5:
    right(); // right autonomous
    break;
  case 6:
    skills(); // skills autonomous
    break;
  } // end of switch case
} // end of autonhandler

void experimental() {
  //TUNED PIDS
  //translate(-4000, 0, 125, 15, 0.055, 0, 4, 0, 2250);
  //translate(4000, 0, 125, 15, 0.055, 0, 4, 0, 2250);
  //turnToHeading(90, 125, 5, 0.3, 0, 20, 0, 3000);
} // end of experimental

void leftWP() {
  farMode(3400);
  angleShiftDown();
  setDrive(-20, -20);
  delay(200);
  rollMatch(1000);
  setDrive(0, 0);
  translate(900, 0, 125, 125, 0.07, 0, 3.5, 0, 1000);
  turnToHeading(-13, 125, 25, 0.5, 0, 20, 0, 1000);
  translate(500, -13, 125, 125, 0.08, 0, 3.5, 0, 1250);

  while (flywheel.get_actual_velocity() * 6 < 3350) {delay(10);}
  shoot();
  delay(350);
  shoot();

  middleMode(3250); // previosuly 3050
  turnToHeading(60, 125, 25, 0.3, 0, 20, 0, 1000);
  setIntake(-127);
  translate(2250, 60, 125, 125, 0.065, 0, 4, 0, 2000);
  setIntake(100);
  translate(1700, 55, 25, 25, 0.075, 0, 3.5, 0, 3000);
  turnToHeading(-35, 125, 25, 0.27, 0, 20, 0, 1000);
  translate(300, -35, 125, 125, 0.095, 0, 3.9, 0, 750);

  shoot();
  delay(250);
  shoot();
  delay(250);
  shoot();

  farMode(3370); // ptrviously 3500
  turnToHeading(41, 125, 25, 0.27, 0, 20, 0, 1000);
  setIntake(100);
  translate(8500, 41, 90, 90, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-90, 125, 25, 0.27, 0, 20, 0, 1000);
  setIntake(0);
  setDrive(-45, -45);
  delay(400);
  setDrive(-20, -20);
  rollMatch(1000);
  translate(700, -79, 125, 125, 0.075, 0, 4, 0, 1000);

  shoot();
  delay(250);
  shoot();
  delay(350);
  shoot();
} // end of left win point

void leftRisk() {
  farMode(3400); // previosuly 3400
  setDrive(-20, -20);
  delay(150);
  rollMatch(1000);
  setIntake(0);
  setDrive(0, 0);
  angleShiftDown();
  intakeLift();
  translate(1000, 0, 125, 125, 0.056, 0, 3.4, 0, 2250);
  turnToHeading(-12, 125, 25, 0.51, 0, 19.9, 0, 3000);
  translate(450, -12, 125, 125, 0.066, 0, 3.3, 0, 2250);

  while (flywheel.get_actual_velocity() * 6 < 3350) {delay(10);}
  shoot();
  delay(350);
  shoot();

  setIntake(127);
  translate(380, -12, 125, 125, 0.066, 0, 3.3, 0, 2250);
  setIntake(127);
  intakeDown();
  delay(1600);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(300);

  shoot();
  delay(350);
  shoot();
  delay(350);
  shoot();

  middleMode(3200);
  translate(-1100, -10, 125, 125, 0.055, 0, 3.5, 0, 2250);
  turnToHeading(45, 125, 25, 0.35, 0, 20, 0, 3000);
  intakeLift();
  setIntake(127);
  translate(2100, 45, 125, 125, 0.055, 0, 3.5, 0, 2250);
  setIntake(127);
  intakeDown();
  delay(1750);
  turnToHeading(-23, 125, 25, 0.31, 0, 19.9, 0, 3000);
  translate(800, -23, 125, 125, 0.066, 0, 3.3, 0, 2250);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(200);

  shoot();
  delay(350);
  shoot();
  delay(350);
  shoot();
} // end of left risk auton

void left() {
  farMode(3150); // previosuly 3400
  setDrive(-20, -20);
  delay(150);
  rollMatch(1000);
  setIntake(0);
  setDrive(0, 0);
  angleShiftDown();
  swingToHeading("right", -45, 125, 25, 0.36, 0, 19.9, 0, 1000);
  setIntake(127);
  translate(400, -45, 125, 125, 0.066, 0, 3.4, 0, 2250);
  translate(-400, -45, 125, 125, 0.066, 0, 3.4, 0, 2250);
  turnToHeading(55, 125, 25, 0.31, 0, 19.9, 0, 3000);
  translate(1800, 55, 125, 125, 0.066, 0, 3.4, 0, 2250);
  turnToHeading(-15, 125, 25, 0.31, 0, 19.9, 0, 3000);
  translate(300, -15, 125, 125, 0.071, 0, 3.4, 0, 2250);

  while (flywheel.get_actual_velocity() * 6 < 3150) {delay(10);}
  shoot();
  delay(400);
  shoot();
  delay(400);
  shoot();

  intakeLift();
  turnToHeading(60, 125, 25, 0.31, 0, 19.9, 0, 3000);
  setIntake(127);
  translate(800, 60, 125, 125, 0.076, 0, 3.4, 0, 2250);
  intakeDown();
  delay(1500);
  turnToHeading(-20, 125, 25, 0.31, 0, 19.9, 0, 3000);
  translate(300, -20, 125, 125, 0.071, 0, 3.3, 0, 2250);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(200);

  shoot();
  delay(400);
  shoot();
  delay(400);
  shoot();

  setIntake(127);
  translate(600, -20, 125, 125, 0.071, 0, 3.3, 0, 2250);
  translate(-600, -20, 125, 125, 0.071, 0, 3.3, 0, 2250);

  shoot();
} //end of left

void right() {
  farMode(3350);
  angleShiftDown();
  setIntake(127);
  translate(2100, 0, 125, 125, 0.065, 0, 3.5, 0, 2000);
  turnToHeading(24.5, 125, 25, 0.36, 0, 19.9, 0, 1000);
  translate(300, 24.5, 125, 125, 0.08, 0, 3.5, 0, 1000);
  delay(300);

  while (flywheel.get_actual_velocity() * 6 < 3300) {delay(10);}
  shoot();
  delay(400);
  shoot();
  delay(400);
  shoot();

  middleMode(3125);
  setIntake(127);
  turnToHeading(45, 125, 25, 0.36, 0, 19.9, 0, 1000);
  translate(900, 45, 125, 125, 0.065, 0, 3.5, 0, 1000);
  translate(-1200, 45, 125, 125, 0.065, 0, 3.5, 0, 2000);
  turnToHeading(-45, 125, 25, 0.31, 0, 19.9, 0, 3000);
  translate(3100, -45, 125, 125, 0.06, 0, 3.4, 0, 3000);
  delay(300);
  turnToHeading(42.5, 125, 25, 0.28, 0, 19.9, 0, 1000);
  translate(400, 42.5, 125, 125, 0.08, 0, 3.5, 0, 1000);

  shoot();
  delay(400);
  shoot();
  delay(400);
  shoot();

  turnToHeading(-45, 125, 125, 0.31, 0, 19.9, 0, 1000);
  translate(-6000, -45, 125, 25, 0.045, 0, 3.5, 0, 3000);
  setDrive(-10, -100);
  delay(450);
  setDrive(-15, -15);
  delay(200);
  rollMatch(1000);
} // end of right auton

void rightRisk() {
  farMode(3100);
  translate(1650, 0, 125, 125, 0.056, 0, 3.4, 0, 2250);
  turnToHeading(-90, 125, 25, 0.31, 0, 19.9, 0, 3000);
  setDrive(-40, -40);
  delay(350);
  rollMatch(1000);
  setDrive(0, 0);
  angleShiftDown();
  intakeLift();
  translate(850, -90, 125, 125, 0.056, 0, 3.4, 0, 2250);
  turnToHeading(-79, 125, 25, 0.51, 0, 19.9, 0, 3000);
  translate(750, -79, 125, 125, 0.056, 0, 3.4, 0, 2250);

  while (flywheel.get_actual_velocity() * 6 < 3100) {delay(10);}
  shoot();
  delay(350);
  shoot();

  setIntake(100);
  translate(450, -79, 125, 125, 0.057, 0, 3.3, 0, 2250);
  intakeDown();
  delay(1400);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(200);

  shoot();
  delay(350);
  shoot();
  delay(350);
  shoot();

  middleMode(3050);
  translate(-900, -78, 125, 125, 0.056, 0, 3.4, 0, 2250);
  turnToHeading(-135, 125, 25, 0.51, 0, 19.9, 0, 3000);
  setIntake(127);
  translate(6000, -135, 70, 70, 0.056, 0, 3.4, 0, 2250);
  turnToHeading(-47, 125, 25, 0.28, 0, 19.9, 0, 3000);
  translate(400, -47, 125, 125, 0.071, 0, 3.4, 0, 3000);

  shoot();
  delay(350);
  shoot();
  delay(350);
  shoot();
} // end of rightRisk auton

void skills() {
  angleShiftDown();
  closeMode();
  setDrive(-20, -20);
  delay(200);
  rollSkills(1000);
  setDrive(0, 0);
  swingToHeading("right", -45, 125, 25, 0.35, 0, 20, 0, 1000);
  setIntake(127);
  translate(900, -45, 125, 125, 0.08, 0, 3.5, 0, 2250);
  turnToHeading(90, 125, 25, 0.23, 0, 20, 0, 3000);
  setIntake(0);
  translate(-1700, 90, 50, 50, 0.055, 0, 3.5, 0, 1000);
  setDrive(-20,-20);
  rollSkills(1000);
  setDrive(0, 0);
  translateDist(false, 510, 90, 125, 125, 0.08, 0, 3.5, 0, 3000);
  turnToHeading(0, 125, 25, 0.3, 0, 20, 0, 3000);
  translateDist(false, 1600, 0, 125, 125, 0.055, 0, 3.5, 0, 3000);
  
  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  turnToHeading(90, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(false, 900, 90, 70, 70, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(45, 125, 25, 0.35, 0, 20, 0, 3000);
  translate(3750, 45, 80, 80, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-45, 125, 25, 0.25, 0, 20, 0, 3000);
  translate(600, -45, 125, 45, 0.055, 0, 3.5, 0, 3000);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(400);

  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  turnToHeading(-90, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(true, 200, -90, 35, 35, 0.08, 0, 3.5, 0, 3000);
  translateDist(true, 1600, -90, 125, 125, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-45, 125, 25, 0.3, 0, 20, 0, 3000);
  
  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  angleShiftUp();
  turnToHeading(0, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(true, 140, 0, 35, 35, 0.08, 0, 3.5, 0, 3000);
  turnToHeading(-93, 125, 25, 0.3, 0, 20, 0, 3000);
  translate(600, -93, 125, 125, 0.08, 0, 3.5, 0, 1000);
  
  discTensionEngage();
  setIntake(-127);
  delay(600);
  setIntake(0);
  discTensionRelease();
  angleShiftDown();

  turnToHeading(-85, 125, 25, 0.7, 0, 20, 0, 3000);
  translate(-3000, -85, 50, 50, 0.055, 0, 3.5, 0, 3000);
  translateDist(false, 700, -90, 125, 125, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-180, 125, 25, 0.35, 0, 20, 0, 3000);
  translate(-1500, -180, 50, 50, 0.055, 0, 3.5, 0, 1000);
  delay(200);
  setDrive(-20,-20);
  rollSkills(1000);
  setDrive(0, 0);
  intakeLift();
  setIntake(127);
  translateDist(false, 725, -180, 125, 125, 0.055, 0, 3.5, 0, 3000);
  intakeDown();
  delay(1000);
  translate(800, -180, 50, 50, 0.07, 0, 3.5, 0, 1500);
  turnToHeading(-90, 125, 25, 0.35, 0, 20, 0, 3000);
  translate(-3000, -90, 50, 50, 0.055, 0, 3.5, 0, 1500);
  delay(200);
  setDrive(-20,-20);
  rollSkills(1000);
  setDrive(0, 0);

  //REPEAT CYCLE
  translateDist(false, 510, -90, 125, 125, 0.08, 0, 3.5, 0, 3000);
  turnToHeading(-180, 125, 25, 0.3, 0, 20, 0, 3000);
  translateDist(false, 1600, -180, 125, 125, 0.055, 0, 3.5, 0, 3000);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(200);

  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  turnToHeading(-90, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(false, 900, -90, 70, 70, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-135, 125, 25, 0.35, 0, 20, 0, 3000);
  translate(3750, -135, 80, 80, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-225, 125, 25, 0.25, 0, 20, 0, 3000);
  translate(500, -225, 125, 45, 0.055, 0, 3.5, 0, 3000);
  setIntake(-127);
  delay(175);
  setIntake(127);
  delay(400);

  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  turnToHeading(-270, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(true, 200, -270, 35, 35, 0.08, 0, 3.5, 0, 3000);
  translateDist(true, 1600, -270, 125, 125, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-225, 125, 25, 0.3, 0, 20, 0, 3000);
  
  shoot();
  delay(100);
  shoot();
  delay(100);
  shoot();

  turnToHeading(-180, 125, 25, 0.3, 0, 20, 0, 3000);
  setIntake(127);
  translateDist(true, 200, -180, 35, 35, 0.08, 0, 3.5, 0, 3000);
  turnToHeading(-273, 125, 25, 0.3, 0, 20, 0, 3000);
  translate(600, -273, 125, 45, 0.055, 0, 3.5, 0, 3000);
  
  discTensionEngage();
  setIntake(-127);
  delay(600);
  setIntake(0);
  discTensionRelease();
  
  translateDist(true, 3300, -270, 125, 125, 0.055, 0, 3.5, 0, 3000);
  turnToHeading(-315, 125, 25, 0.3, 0, 20, 0, 3000);
  expand();
} // end of skills