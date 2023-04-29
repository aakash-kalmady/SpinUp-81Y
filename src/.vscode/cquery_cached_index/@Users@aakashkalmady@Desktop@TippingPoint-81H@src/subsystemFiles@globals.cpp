#include "main.h"
using namespace pros;

//MOTORS
Motor lift(5, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);
Motor ringMech(9, MOTOR_GEARSET_6, false, E_MOTOR_ENCODER_COUNTS);
Motor driveLB(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor driveRM(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor driveLF(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor driveRB(8, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor driveLM(6, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor driveRF(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

//CONTROLLER
Controller controller(pros::E_CONTROLLER_MASTER);

//INERTIAL SENSOR
Imu inertial_sensor(12);

//DISTANCE SENSORS
Distance distF(16);
Distance distB(15);

//GPS
Gps gps1(1);

//DRIVE ENCODERS
ADIEncoder encoderLeft ('C', 'D', true);
//ADIEncoder encoderRight ('A', 'B', false);
ADIEncoder encoderAux ('C', 'D', true);

//POTENTIOMETERS
ADIAnalogIn armPot ('B');
ADIAnalogIn draggerPot ('B');

//LIMIT SWITCH FOR AUTONHANDLER
ADIDigitalIn autonSelector('D');
ADIDigitalOut claw('E');
ADIDigitalOut mogoMech('A');
