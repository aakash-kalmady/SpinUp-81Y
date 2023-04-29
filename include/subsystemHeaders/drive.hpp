#include "main.h"
#include <string>
using namespace pros;
using namespace std;
/*
* @func: Sets the voltage of the drive
*   @param: Left wheel voltage
*   @param: Right wheel voltage
*/
extern void setDrive(int left, int right);
/*
* @func: Resets the drive motor encoders
*/
extern void resetDriveEncoders();
/*
* @func: Determines the encoder value of the tracking wheel
*   @return: Encoder wheel value
*/
extern float encoderValue();
/*
* @func: Resets the tracking wheel's encoder value
*/
extern void resetEncoder();
/*
* @func: Determines the encoder aux value of the tracking wheel
*   @return: Encoder Aux wheel value
*/
extern float encoderAuxValue();
/*
* @func: Resets the aux tracking wheel's encoder value
*/
extern void resetAuxEncoder();
/*
* @func: Sets the brake mode of the drive
*   @return: Encoder wheel value
*/
extern void setBrakeMode(string brakeMode);
/*
* @func: Determines the average drive encoder value of the drive
*   @return: Average drive encoder value
*/
extern float avgDriveEncoderValue();
/*
* @func: Determines the front distance sensor value
*   @return: Front distance sensor value in mm
*/
extern int frontDistanceSensorValue();
/*
* @func: Determines the back distance sensor value
*   @return: Back distance sensor value in mm
*/
extern int backDistanceSensorValue();
/*
* @func: Determines the drive's left motor encoder value
*   @return: Average left motor encoder value
*/
extern float leftDriveEncoderValue();
/*
* @func: Determines the drive's right motor encoder value
*   @return: Average right motor encoder value
*/
extern float rightDriveEncoderValue();
/*
* @func: Determines the IMU's heading
*   @return: Yaw of IMU in degrees
*/
extern float inertialRotationValue();
/*
* @func: Determines the IMU's roll
*   @return: Roll of IMU in degrees
*/
extern float inertialRollValue();
/*
* @func: Determines the IMU's pitch
*   @return: Pitch of IMU in degrees
*/
extern float inertialPitchValue();
/*
* @func: Controls the drivetrain using a exponential/curve tank control
*/
extern void driveOPTankCurve();
/*
* @func: Controls the drivetrain normally through tank control
*/
extern void driveOPTankReg();
/*
* @func: Controls the drivetrain through arcade control
*/
extern void driveOPArcade();
/*
* @func: Translates drive to certain set point
*/
extern void translate(int setPoint, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime);
/*
* @func: Translates drive to certain distance from the field perimeter
*/
extern void translateDist(bool sensorType, int desiredDistance, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime);
/*
* @func: Rotates drive to a certain set heading
*/
extern void turnToHeading(float setPoint, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime);
/*
* @func: Swing turns drive to a certain set heading
*/
extern void swingToHeading(string baseSide, int setPoint, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime);

