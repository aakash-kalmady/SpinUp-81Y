#include "main.h"
#include <string>
using namespace pros;
using namespace std;

//MOTORS
extern Motor intake, flywheel, driveLB, driveLM, driveLF, driveRB, driveRM, driveRF;

//CONTROLLER
extern Controller controller;

//SENSORS
extern ADIDigitalIn autonSelector;
extern ADIAnalogIn shotTracker;
extern IMU inertial_sensor;
extern Distance distF, distB;
extern ADIDigitalOut expansion, angleShifter, discTension, intakeTension;
extern Rotation encoder, encoderAux;

//TASKS
extern Task *flywheelOPTask, *trackPos;
