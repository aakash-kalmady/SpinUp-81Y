#include "main.h"
using namespace pros;

//MOTORS
Motor driveRM(14, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor driveRB(13, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor driveRF(12, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor driveLB(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor driveLM(21, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor driveLF(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor intake(1, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor flywheel(11, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);

//CONTROLLER
Controller controller(E_CONTROLLER_MASTER);

//LIMIT SWITCH
ADIDigitalIn autonSelector('F');

//INERTIAL SENSOR
Imu inertial_sensor(16);

//DISTANCE SENSORS
Distance distF(9), distB(3);

//PNEUMATICS
ADIDigitalOut expansion('E'), angleShifter('D'), discTension('B'), intakeTension('C');

//LINE SENSORS
ADIAnalogIn shotTracker('A');

//ROTATION SENSORS 
Rotation encoder(17), encoderAux(15);

//TASKS
Task *flywheelOPTask = nullptr, *trackPos = nullptr;
