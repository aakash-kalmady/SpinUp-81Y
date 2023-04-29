#include "main.h"
#include <string>
using namespace pros;
using namespace std;
//autonomous global integer used for auton selector
int auton = 0;

//******************************************************************************
//
//a callback function for LLEMU's center button.
//
//when this callback is fired, it will toggle line 2 of the LCD text between
//"I was pressed!" and nothing.
//
//******************************************************************************

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

//******************************************************************************
//
//runs initialization code. This occurs as soon as the program is started.
//
//all other competition modes are blocked by initialize; it is recommended
//to keep execution time for this mode under a few seconds.
//
//******************************************************************************

void initialize() {
	lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	//initializing the brain screen
	delay(200);
	lcd::initialize();
	lcd::register_btn1_cb(on_center_button);
	//initializing potentiometers
	ADIAnalogIn armPot ('E');
	ADIAnalogIn draggerPot ('B');
	//initializing the limit switch, or the auton selector
	ADIDigitalIn autonSelector('D');
	//initializing the distance sensors
	Distance distF(16);
	Distance distB(15);
	//initializing gps
	Gps gps1(1, -0.1905, 0.0635);
	//initializing odometers
	ADIEncoder encoderLeft ('C', 'D', false);
	//ADIEncoder encoderRight ('A', 'B', true);
	ADIEncoder encoderAux ('C', 'D', true);
	//initializing pneumatics
	ADIDigitalOut claw('E');
	ADIDigitalOut mogoMech('A');
	//initializing IMUs & calibrating them, errors were resolved by updating kernel and changing ports
	Imu inertial_sensor(12);
	inertial_sensor.reset();
	delay(2500);
}

//******************************************************************************
//
//runs while the robot is in the disabled state of Field Management System or
//the VEX Competition Switch, following either autonomous or opcontrol. When
//the robot is enabled, this task will exit.
//
//******************************************************************************

void disabled() {}

//******************************************************************************
//
//runs after initialize(), and before autonomous when connected to the Field
//management System or the VEX Competition Switch. This is intended for
//competition-specific initialization routines, such as an autonomous selector
//on the LCD.
//
//this task will exit when the robot is enabled and autonomous or opcontrol
//starts.
//
//******************************************************************************

void competition_initialize() {
	/*
	//autonomous selector using limit switch
	const int autoCount = 6;
	const char* autoNames[autoCount] = {
		"Test",
		"Right Win Point",
		"Win Point (both sides)",
		"Right Neutral Goal",
		"Left Neutral Goal",
		"Skills",
	};
	//displaying on the brain screen
	lcd::set_text(0, "Select an Autonomous");
	lcd::print(2, "%s", autoNames[auton]);
	//feedback loop with the limit switch
	while(true){
		if(autonSelector.get_new_press()) {
			auton++;
			if(auton == autoCount) {
				auton = 0;
			} //end of if
			lcd::print(2, "%s", autoNames[auton]);
			lcd::print(3, "%d", auton);
		} //end of if
		//dont update too quickly
		delay(50);
	} //end of while
	*/
} //end of competition initialize

//******************************************************************************
//
//runs the user autonomous code. This function will be started in its own task
//with the default priority and stack size whenever the robot is enabled via
//the Field Management System or the VEX Competition Switch in the autonomous
//mode. Alternatively, this function may be called in initialize or opcontrol
//for non-competition testing purposes.
//
//if the robot is disabled or communications is lost, the autonomous task
//will be stopped. Re-enabling the robot will restart the task, not re-start it
//from where it left off.
//
//******************************************************************************

void autonomous() {
	//autonhandler(auton);
	//park();
	//experimental();
	//null();
	rightWP();
	//rightStraight();
	//winPoint();
	//skills();
} //end of autonomous

//******************************************************************************
//
//runs the operator control code. This function will be started in its own task
//with the default priority and stack size whenever the robot is enabled via
//the Field Management System or the VEX Competition Switch in the operator
//control mode.
//
//if no competition control is connected, this function will run immediately
//following initialize().
//
//if the robot is disabled or communications is lost, the
//operator control task will be stopped. Re-enabling the robot will restart the
//task, not resume it from where it left off.
//
//******************************************************************************

void opcontrol() {
	int startTime = millis();
	int elapsedTime;
	string displayHeading;
	string displayDisplacement;
	while(true) {
		//operate the robot
		driveOP();
		liftOP();
		clampOP();
		mogoMechOP();
		ringMechOP();
		controller.print(0, 0, "Distance: %d", distF.get());
		//odomTrackPosition();
		//display the get_rotation value on the brain during driver mode
		displayHeading = to_string(inertialRollValue());
		displayDisplacement = to_string(avgDriveEncoderValue());
		lcd::set_text(4, displayHeading);
		lcd::set_text(5, displayDisplacement);
		if (controller.get_digital(E_CONTROLLER_DIGITAL_A) == 1) {
			resetDriveEncoders();
		}
		//if 30 seconds is remaining in the match, rumble the controller
		elapsedTime = millis() - startTime;
		if (70000 < elapsedTime && elapsedTime < 75000) {
			controller.rumble(".- .- .-");
		} //end of if
		delay(50); //dont update too quickly
	} //end of while
} //end of opcontrol
