#include "main.h"
#include <string>
#include "display/lvgl.h"
using namespace pros;
using namespace std;
using namespace lcd;

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
		set_text(2, "I was pressed!");
	} else {
		clear_line(2);
	}
} //end of on center button

//******************************************************************************
//
//runs initialization code. This occurs as soon as the program is started.
//
//all other competition modes are blocked by initialize; it is recommended
//to keep execution time for this mode under a few seconds.
//
//******************************************************************************

void initialize() {
	//INITIALIZE LOADING BAR
	lv_style_t style1 = lv_style_pretty, style2 = lv_style_btn_tgl_pr;
  	style1.body.main_color = LV_COLOR_WHITE, style1.body.grad_color = LV_COLOR_WHITE, style2.body.border.color = LV_COLOR_WHITE, style2.body.main_color = LV_COLOR_BLACK, style2.body.grad_color = LV_COLOR_BLACK;
	lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar1, 410, 150);
    lv_obj_align(bar1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_bar_set_value_anim(bar1, 100, 2000);
	lv_bar_set_style(bar1, LV_BAR_STYLE_INDIC, &style1);
	lv_bar_set_style(bar1, LV_BAR_STYLE_BG, &style2);
	//SET BRAKE MODES
	intake.set_brake_mode(E_MOTOR_BRAKE_COAST);
	flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
	driveLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRB.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRM.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveLM.set_brake_mode(E_MOTOR_BRAKE_COAST);
	//INITIALIZE INERTIAL SENSOR
	inertial_sensor.reset();
	//INITIALIZE ROTATION SENSORS
	encoder.set_data_rate(5), encoderAux.set_data_rate(5);
	encoder.set_reversed(false), encoderAux.set_reversed(false);
	encoder.reset_position(), encoderAux.reset_position();
	//DELAY IF INERTIAL IS STILL CALIBRATING
	delay(2000);
	//ODOMETRY TASK
	trackPos = new Task(trackPosition, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "trackPos");
	//FLYWHEEL CONTROL TASK
	flywheelOPTask = new Task(flywheelOP, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "flywheelOPTask");
	//INITIALIZE BRAIN SCREEN
	lcd::initialize();
	set_background_color(LV_COLOR_BLACK);
	set_text_color(LV_COLOR_WHITE);
	register_btn1_cb(on_center_button);
} //end of initialize

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

bool competition_state = false;
int auton = 0;
const int autoCount = 7;
const char* autoNames[autoCount] = {
	"Experimental",
	"8 Disc AWP",
	"8 Disc Left High Risk Auton",
	"7 Disc Left Auton",
	"8 Disc Right High Risk Auton",
	"6 Disc Right Auton",
	"Skills Auton",
};

void competition_initialize() {
	competition_state = true;
	//displaying on the brain screen
	clear();
	set_text(1, "Select an Autonomous Program");
	print(2, "%s", autoNames[auton]);
	//feedback loop with the limit switch
	while(true) {
		if(autonSelector.get_new_press()) {
			auton++;
			if(auton == autoCount) {auton = 0;}
			print(2, "%s", autoNames[auton]);
			print(3, "%d", auton);
		} //end of if
		//dont update too quickly
		delay(10);
	} //end of while
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
	autonHandler(auton);
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
	shooting = false;
	closeMode();
	angleShiftUp();
	int startTime = millis();
	int encoder, distF, distB, RPM;
	string displayHeading, displayDisplacement, displayDistB, displayDistF, displayRPM, displayShotTrackerValue;
	while(true) {
		driveOPArcade(), intakeOP(), expansionOP(), intakeTensionOP();
		encoder = encoderValue() / 40, distF = frontDistanceSensorValue(), distB = backDistanceSensorValue();
		//display heading and displacement values
		displayHeading = to_string(inertialRotationValue()), displayDisplacement = to_string(encoder);
		//display distance sensor values
		displayDistF = to_string(distF), displayDistB = to_string(distB);
		//display line sensor value for shot detection
		displayShotTrackerValue = to_string(shotTrackerValue());
		//project values onto brain screen
	    set_text(1, "Heading Angle: " + displayHeading);
		set_text(2, "Encoder: " + displayDisplacement);
		set_text(3, "DistF: " + displayDistF + "  DistB: " + displayDistB);
		set_text(4, "Disc Tracker Value: " + displayShotTrackerValue);
		//reset encoder wheel if A is pressed
		if (controller.get_digital_new_press(DIGITAL_A)) {resetEncoder();}
		delay(10); //dont update too quickly
	} //end of while
} //end of opcontrol