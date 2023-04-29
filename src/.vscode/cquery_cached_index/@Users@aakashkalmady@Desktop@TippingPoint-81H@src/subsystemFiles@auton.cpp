#include "main.h"
#include <string>
using namespace pros;
using namespace std;
/*
void autonhandler(int auton) {
  experimental();
  //switch case, compare auton int to values below
  switch(auton) {
      case 0:
        experimental(); //testing auton
        break;
      case 1:
        rightWP(); //right side win point
        break;
      case 2:
        //winPoint(); //win point
        break;
      case 3:
        rightStraight(); //right side high risk auton
        break;
      case 4:
        leftStraight(); //left side high risk auton
        break;
      case 5:
        skills(); //skills autonomous
        break;
   }
} //end of autonhandler
*/

void deploy() {
  clampMogo();
  delay(75);
  releaseMogo();
}
void null() {
clampMogo();
delay(300);
releaseMogo();

setDrive(-40,-40);
delay(500);
setDrive(0,0);
clampMogo();

setLift(127);
delay(400);
setLift(0);

setRingMech(127);
delay(1000);
translate(1000, 0, 125, 7, 0.182, 0, 10, 0, 1300);
setRingMech(0);
}
//if we want to make movements liek that, we have to constantly caculate the new angle to look ahead at the coordiate we want to go to. Then, we can constantly turn to tface this headigng in just a transalte function.
void experimental() {

deploy();
setLift(-80);
releaseClamp();

translateDist(false, 855, 0, 125, 8, 0.182, 0, 10, 0, 1000);

turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 800); //perfectly tuned 90 degree turn

translate(-900, -90, 60, 8, 0.182, 0, 10, 0, 1100);
setDrive(-40,-40);
delay(350);
clampMogo();
delay(100);

translate(1150, -90, 125, 8, 0.182, 0, 10, 0, 1300);

turnToHeading(0, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn

//translate(1500, 0, 125, 8, 0.182, 0, 10, 0, 5000);
translateDist(false, 1500, 0, 125, 8, 0.182, 0, 20, 0, 1300);

clamp();

setLift(127);
delay(1500);
setLift(10);

translate(1950, 0, 100, 8, 0.182, 0, 20, 0, 2000);

setRingMech(127);
turnToHeading(-90, 125, 8, 0.21, 0, 12, 0, 1500); //perfectly tuned 90 degree turn

translateDist(false, 1625, -90, 60, 8, 0.182, 0, 10, 0, 2000);
translate(800, -90, 60, 8, 0.182, 0, 20, 0, 1500);
translate(-500, -90, 60, 8, 0.182, 0, 20, 0, 1500);
setRingMech(-127);
delay(300);
setRingMech(127);
//translate(2300, -45, 70, 8, 0.182, 0, 20, 0, 2500);
turnToHeading(0, 125, 8, 0.218, 0, 12, 0, 500); //perfectly tuned 90 degree turn
setDrive(50,50);
delay(1000);
setDrive(0,0);

setRingMech(0);
setLift(-127);
delay(600);
setLift(0);
delay(200);
releaseClamp();
setLift(127);
delay(300);

setLift(-70);

translate(-1200, 0, 70, 8, 0.182, 0, 20, 0, 1500);

releaseMogo();

translate(800, 0, 70, 8, 0.182, 0, 20, 0, 1500);

turnToHeading(180, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn

translate(710, 180, 70, 8, 0.182, 0, 20, 0, 1000);

clamp();
setLift(10);

turnToHeading(15, 125, 8, 0.19, 0, 12, 0, 1500); //perfectly tuned 90 degree turn
setLift(127);
setRingMech(127);
delay(1000);
translate(900, 15, 70, 8, 0.182, 0, 20, 0, 1500);
setLift(-127);
setRingMech(0);
delay(500);
setLift(0);
delay(100);
releaseClamp();
setLift(127);
translate(-300, 0, 125, 8, 0.182, 0, 20, 0, 1000);

turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn
setLift(-90);

translateDist(false, 400, -90, 125, 8, 0.182, 0, 10, 0, 3000);

turnToHeading(-45, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn

translate(1225, -45, 125, 8, 0.182, 0, 20, 0, 1500);

clamp();
setLift(10);

translate(-1270, -37, 125, 8, 0.182, 0, 20, 0, 1500);

turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn
setLift(127);
delay(1000);
setRingMech(-127);
delay(300);
setRingMech(127);
translate(4200, -90, 125, 8, 0.182, 0, 20, 0, 2800);
setLift(-127);
delay(1000);
setLift(10);
turnToHeading(-270, 125, 8, 0.2, 0, 13, 0, 1500); //perfectly tuned 90 degree turn
translate(-900, -270, 125, 8, 0.182, 0, 20, 0, 1000);
setDrive(-40,-40);
delay(2000);
clampMogo();
delay(100);
setLift(127);
delay(500);

translate(5400, -270, 125, 8, 0.182, 0, 12, 0, 3500);
turnToHeading(-180, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn
setRingMech(-127);
delay(200);
setRingMech(127);
translate(4700, -180, 55, 8, 0.182, 0, 10, 0, 6000);
setDrive(50,50);
delay(2000);
setDrive(0,0);
setRingMech(-127);
delay(200);
setRingMech(127);
translate(-410, -180, 125, 8, 0.182, 0, 10, 0, 1000);
turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn
translate(490, -90, 50, 8, 0.182, 0, 10, 0, 1000);
setRingMech(0);
setLift(-127);
delay(900);
//insert parking code here
park();






/*
setLift(-50);
releaseClamp();
setDrive(127, 127);
delay(950);
setLift(0);
clamp();
setDrive(0,0);
setLift(127);
delay(100);
setLift(10);

setDrive(-127, -127);
delay(7000);
setDrive(-70,-70);
delay(1200);
setDrive(0,0);
*/

/*
translate(1430, 0, 125, 7, 0.182, 0, 10, 0, 1300);
turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 1000);
clampMogo();
delay(75);
releaseMogo();

translate(-500, -90, 125, 7, 0.182, 0, 10, 0, 800);
setDrive(-50, -50);
delay(1000);
clampMogo();
delay(200);
setRingMech(127);
delay(500);
translate(1000, -90, 125, 7, 0.185, 0, 10, 0, 1000);
setRingMech(0);
*/


/*

  float distance = 2600;
  while(avgDriveEncoderValue < distance) {
    setDrive(127, 127);
  }
  clamp();
  delay(200);
  setDrive(0,0);
  setBrakeMode("HOLD");


  delay(500);

  setDrive(-127,127);
  delay(1000);

  translateDist(false, 850, -90, 125, 7, 0.182, 0, 10, 0, 1300);
  turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 800);
  translate(-1000, -90, 60, 7, 0.185, 0, 10, 0, 1000);

  clampMogo();
  setRingMech(127);
  delay(1000);
  translate(1000, -90, 125, 7, 0.185, 0, 10, 0, 1000);
  */

/*

  setClaw(127);
  setLift(-50);
  delay(70);
  setClaw(0);
  translate(5000, 0, 125, 7, 0.185, 0, 20, 0, 2900); //perfectly tuned
  translate(-1000, 0, 125, 7, 0.185, 0, 10, 0, 1000); //perfectly tuned
  turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translateDist(false, 850, -90, 125, 7, 0.182, 0, 10, 0, 1300);
  turnToHeading(-180, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translate(1500, -180, 125, 7, 0.185, 0, 10, 0, 1350); //perfectly tuned
  setClaw(-127);
  delay(600);
  translateDist(true, 1460, -180, 125, 7, 0.182, 0, 10, 0, 800);
  turnToHeading(-135, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  setLift(127);
  delay(700);
  translate(2160, -135, 125, 7, 0.185, 0, 10, 0, 1900); //perfectly tuned
  setLift(-127);
  delay(600);
  setLift(127);
  delay(150);
  setLift(0);
  turnToHeading(-180, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  setClaw(127);
  delay(300);
  setClaw(0);
  setLift(127);
  delay(70);
  setLift(0);
  translate(-1500, -180, 125, 7, 0.185, 0, 10, 0, 1900); //perfectly tuned
  turnToHeading(-270, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translateDist(true, 1360, -270, 125, 7, 0.182, 0, 10, 0, 800);
  turnToHeading(-225, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translate(-3500, -225, 80, 7, 0.185, 0, 10, 0, 2500); //perfectly tuned
  translate(2000, -225, 80, 7, 0.185, 0, 10, 0, 2500); //perfectly tuned
  delay(100000);

  setClaw(127);
  delay(200);
  setClaw(-127);
  delay(350);
  setClaw(0);
  setLift(-127);
  translate(3000, inertialRotationValue(), 125, 7, 0.182, 0, 20, 0, 1400); //perfectly tuned


  translate(-2400, inertialRotationValue(), 125, 7, 0.182, 0, 10, 0, 1500);
  setClaw(127);
  delay(200);
  setClaw(0);
  translate(-600, inertialRotationValue(), 125, 7, 0.182, 0, 10, 0, 1500);

  turnToHeading(-135, 125, 7, 0.263, 0, 10, 0, 1500); //currently being tuned

  translate (-1400, -135, 60, 7, 0.18, 0, 20, 0, 1500); //perfectly tuned
  setMogoMech(-127);
  setRingMech(127/1.5);
  delay(1500);
  translate(1000, -135, 125, 7, 0.182, 0, 20, 0, 1400);

  /*
  //grap mogo in middle
  translate (-2650, 0, 125, 7, 0.18, 0, 20, 0, 1500); //perfectly tuned
  setMogoMech(-127);
  delay(175);

  //come back
  translate (2000, 0, 125, 7, 0.182, 0, 10, 0, 1500); //perfectly tuned

  //deploy mogo
  setMogoMech(127);
  delay(175);
  setMogoMech(0);

  translate (725, 0, 125, 7, 0.182, 0, 10, 0, 1000); //perfectly tuned

  turnToHeading(45, 125, 7, 0.263, 0, 10, 0, 1500); //currently being tuned

  translate (-1500, 45, 60, 7, 0.18, 0, 20, 0, 1500); //perfectly tuned
  setMogoMech(-127);
  setClaw(127);
  delay(200);
  setClaw(0);
  setLift(127);
  delay(600);
  setLift(0);
  setRingMech(127/1.5);
  setDrive(35,35);
  delay(2000);
  setDrive(-35,-35);
  delay(1500);
  setDrive(35,35);
  delay(1500);
  setDrive(0,0);
  delay(700);
  setRingMech(0);
  */

  /*
  translate (-725, 0, 125, 5, 0.182, 0, 10, 0, 1000); //perfectly tuned
  turnToHeading(-90, 125, 5, 0.263, 0, 10, 0, 1000); //currently being tuned
  translate (600, -90, 125, 5, 0.3, 0, 10, 0, 1000);
  turnToHeading(-165, 125, 5, 0.263, 0, 10, 0, 1500); //currently being tuned
  translate (900, -165, 125, 5, 0.182, 0, 10, 0, 1000);
  turnToHeading(-150, 125, 5, 0.263, 0, 10, 0, 1500); //currently being tuned
  translate (2900, -150, 125, 5, 0.182, 0, 10, 0, 1000);
  turnToHeading(-180, 125, 5, 0.263, 0, 10, 0, 1500);
  translate (-1100, -180, 125, 5, 0.182, 0, 10, 0, 1000);
  turnToHeading(-225, 125, 5, 0.263, 0, 10, 0, 1500);
  translate (-3000, -225, 125, 5, 0.182, 0, 10, 0, 1000);
  */
  //translateDist(true, 400, 0, 125, 10, 0.2, 0, 10, 0, 1000);

  //turnToHeading(-135, 125, 5, 0.25, 0, 10, 0, 1500);
  //translate(2000, -135, 125, 5, 0.182, 0, 10, 0, 3000);
} //end of experimental

//This autonomous function clears the win point line on the right side first, then goes on the left side of the field and deploys rings in mogo
void rightWP() {
  releaseClamp();
  setLift(-30);
  while(distB.get() < 1430) {
    setDrive(127 - inertialRotationValue() * 6, 127 + inertialRotationValue() * 6);
    delay(10);
  }
  setDrive(0,0);
  clamp();
  delay(100);
  while(distB.get() > 500) {
    setDrive(-127 - inertialRotationValue() * 6, -127 + inertialRotationValue() * 6);
    delay(10);
  }
  setDrive(-40,-40);
  delay(500);
  setLift(10);

  translateDist(false, 870, 0, 125, 8, 0.182, 0, 10, 0, 2000);

  deploy();

  turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn

  translate(-600, -90, 125, 8, 0.182, 0, 10, 0, 1500);

  setDrive(-40,-40);
  delay(825);
  clampMogo();
  delay(50);
  setLift(127);
  setRingMech(127);
  translate(1000, -90, 125, 8, 0.182, 0, 10, 0, 1500);
} //end of winPoint autonomous

//This autonomous function gets the yellow neutral goal from the middle first, then proceeds to score the win point only on the right side
void rightStraight() {
  /*
  //grap mogo in middle
  translate (-2750, 0, 125, 7, 0.18, 0, 30, 0, 1500); //perfectly tuned
  setMogoMech(-127);
  delay(175);

  //come back
  translate (2075, 0, 125, 7, 0.182, 0, 10, 0, 1500); //perfectly tuned

  //deploy mogo
  setMogoMech(127);
  delay(175);
  setMogoMech(0);

  translate (725, 0, 125, 7, 0.182, 0, 10, 0, 1000); //perfectly tuned

  turnToHeading(45, 125, 7, 0.263, 0, 10, 0, 1500); //currently being tuned

  translate (-1500, 45, 60, 7, 0.18, 0, 20, 0, 1500); //perfectly tuned
  setMogoMech(-127);
  setClaw(127);
  delay(200);
  setClaw(0);
  setLift(127);
  delay(600);
  setLift(0);
  setRingMech(127/1.5);
  setDrive(35,35);
  delay(2000);
  setDrive(-35,-35);
  delay(1500);
  setDrive(35,35);
  delay(1500);
  setDrive(0,0);
  delay(700);
  setRingMech(0);
  */
}

//This autonomous function deploys rings on the left mogo, and proceeds to get the yellow neutral mogo from the center
void leftStraight() {
  /*
		//setDragger(-127);
		//translate(-2450, 120, 2, 0.21, 0, 0.5, 120, 5000);

	  //drag();

		//translate(2000, 80, 3, 0.15, 0, 0.5, 120, 5000);
		//resetDragger();

		setDrive(50, 50);
		delay(1000);
		setDrive(0,0);

		delay(200);

		//translate(-200, 80, 2, 0.23, 0, 0.5, 120, 1500);

		turnToHeading(-90, 70, 2, 1.4, 0, 5, 120, 1500);

		setLift(-50);

		setDrive(30, 30);
		delay(1000);
		setDrive (0,0);

		clamp();

		setClaw(127);
		delay(400);
		setClaw(0);

		//translate(-1000, 80, 2, 0.16, 0, 0.5, 120, 2000);
*/
} //end of leftStraight autonomous

void skills() {

  //move forward initially
  translate(5000, 0, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn to pick up mogo with back
  turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //translate back to pick up mogo
  translate(-1000, -90, 125, 7, 0.185, 0, 20, 0, 2900);

  //clamp onto mogo with mogoMech
  clampMogo();
  delay(200);

  //translate backward
  translate(1000, -90, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn to face yellow Goal
  turnToHeading(0, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move foward towards neutral Goal
  translate(1000, 0, 125, 7, 0.185, 0, 20, 0, 2900);

  //clamp onto neutral mogo
  clamp();

  //translate a little forward
  translate(1000, 0, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn to face platform
  turnToHeading(-45, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move towards platform
  translate(1000, -45, 125, 7, 0.185, 0, 20, 0, 2900);

  //insert release code here
  //
  //
  //
  //

  //move backwards away from platform
  translate(-1000, -45, 125, 7, 0.185, 0, 20, 0, 2900);

  //release back mogo
  releaseMogo();
  delay(200);

  //move forward to create room to 180
  translate(500, -45, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn 180
  turnToHeading(135, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move forward to grap mogo
  translate(500, 135, 125, 7, 0.185, 0, 20, 0, 2900);

  //clamp onto aliance mogo that was in the back of our robot
  clamp();

  //insert raise arm code here
  //
  //
  //
  //

  //turn 180 to face platform
  turnToHeading(-45, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move forward towards platform
  translate(1000, 135, 125, 7, 0.185, 0, 20, 0, 2900);

  //insert release code here
  //
  //
  //
  //

  //move back a bit
  translate(-500, 135, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn to heading -90 to pick up mogo underneath platform
  turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move backward
  translate(-2000, -90, 125, 7, 0.185, 0, 20, 0, 2900);

  //turn to face mogo underneath platform
  turnToHeading(-45, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned

  //move forward towards mogo undernath platform
  translate(1000, -45, 125, 7, 0.185, 0, 20, 0, 2900);

  //clamp onto mogo underneath platform
  clamp();

  /*
  setClaw(127);
  setLift(-50);
  delay(70);
  setClaw(0);
  translate(5000, 0, 125, 7, 0.185, 0, 20, 0, 2900); //perfectly tuned
  translate(-1000, 0, 125, 7, 0.185, 0, 10, 0, 1000); //perfectly tuned
  turnToHeading(-90, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translateDist(false, 850, -90, 125, 7, 0.182, 0, 10, 0, 1300);
  turnToHeading(-180, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translate(1500, -180, 125, 7, 0.185, 0, 10, 0, 1350); //perfectly tuned
  setClaw(-127);
  delay(600);
  translateDist(true, 1460, -180, 125, 7, 0.182, 0, 10, 0, 800);
  turnToHeading(-135, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  setLift(127);
  delay(700);
  translate(2160, -135, 125, 7, 0.185, 0, 10, 0, 1900); //perfectly tuned
  setLift(-127);
  delay(600);
  setLift(127);
  delay(150);
  setLift(0);
  turnToHeading(-180, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  setClaw(127);
  delay(300);
  setClaw(0);
  setLift(127);
  delay(70);
  setLift(0);
  translate(-1500, -180, 125, 7, 0.185, 0, 10, 0, 1900); //perfectly tuned
  turnToHeading(-270, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translateDist(true, 1360, -270, 125, 7, 0.182, 0, 10, 0, 800);
  turnToHeading(-225, 125, 7, 0.263, 0, 10, 0, 800); //currently being tuned
  translate(-3500, -225, 80, 7, 0.185, 0, 10, 0, 2500); //perfectly tuned
  translate(2000, -225, 80, 7, 0.185, 0, 10, 0, 2500); //perfectly tuned
  */
} //end of skills

void winPoint() {

  deploy();

  translateDist(false, 855, 0, 125, 8, 0.182, 0, 10, 0, 2000);

  turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn

  translate(-600, -90, 125, 8, 0.182, 0, 10, 0, 1500);

  setDrive(-40,-40);
  delay(825);
  clampMogo();
  delay(50);
  setLift(60);
  translate(500, -90, 125, 8, 0.182, 0, 10, 0, 1000);
  setLift(0);
  turnToHeading(-45, 125, 8, 0.218, 0, 12, 0, 600); //perfectly tuned 90 degree turn
  translate(1000, -45, 125, 8, 0.182, 0, 10, 0, 1500);
  turnToHeading(-90, 125, 8, 0.218, 0, 12, 0, 600); //perfectly tuned 90 degree turn
  setRingMech(127);
  translate(4170, -90, 50, 8, 0.182, 0, 10, 0, 5000);
  translate(-900, -90, 125, 8, 0.182, 0, 10, 0, 1000);
  turnToHeading(-180, 125, 8, 0.218, 0, 12, 0, 1000); //perfectly tuned 90 degree turn
  translate(1150, -180, 125, 8, 0.182, 0, 10, 0, 1000);
  releaseClamp();
  translate(-200, -180, 125, 8, 0.182, 0, 10, 0, 500);
  releaseMogo();


} //end of winPoint

void park() {
  while(inertialRollValue() > -15) {
    setDrive(127,127);
    delay(10);
  }
  delay(1000);
  float roll = inertialRollValue();
  string displayDisplacement = to_string(roll);
  lcd::set_text(2, displayDisplacement);
  while(inertialRollValue() < -20) {
    setDrive(65,65);
    delay(10);
  }
  setBrakeMode("HOLD");
  setDrive(-20,-20);
  delay(10);
  setDrive(0,0);
  releaseClamp();
  releaseMogo();
  /*
  float tilt = 0;
  float lastTilt = 0;
  bool parked = false;
  float tDeriv = 0;
  setDrive(127, 127);
  delay(400);
  while(!parked) {
    float tilt = inertialRollValue() * -1;
    if (-1 < tilt < 1) {
      tilt = 0;
    }
    tDeriv = (tilt - lastTilt) / 10;
    lastTilt = tilt;
    if (sign(tDeriv) == -1) {
      parked = true;
    }
    delay(10);
  }
  releaseMogo();
  releaseClamp();
  setDrive(0,0);
  */
}
