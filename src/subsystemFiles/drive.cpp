#include "main.h"
#include <string>
using namespace pros;
using namespace std;

//******************************************************************************
//
//HELPER FUNCTIONS
//
//these functions are to be used both during driver control and autonomous
//to simplify the code
//
//******************************************************************************

void setDrive(int left, int right) {
  driveLF = left, driveLM = left, driveLB = left, driveRF = right, driveRM = right, driveRB = right;
} //end of setDrive

void resetDriveEncoders() {
  driveLB.tare_position();
  driveLF.tare_position();
  driveRB.tare_position();
  driveRF.tare_position();
  driveRM.tare_position();
  driveLM.tare_position();
} //end of resetDriveEncoders

float encoderValue() {
  return encoder.get_position();
} //end of encoderValue

float encoderAuxValue() {
  return encoderAux.get_position();
} //end of encoderValue

void resetEncoder() {
  encoder.reset_position();
} //end of resetEncoder

void resetAuxEncoder() {
  encoderAux.reset_position();
} //end of resetEncoder

void setBrakeMode(string brakeMode) {
  if (brakeMode == "COAST") {
    driveLB.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveLF.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRB.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveRM.set_brake_mode(E_MOTOR_BRAKE_COAST);
    driveLM.set_brake_mode(E_MOTOR_BRAKE_COAST);
  } else if (brakeMode == "BRAKE") {
    driveLB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    driveLF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    driveRB.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    driveRF.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    driveRM.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    driveLM.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  } else {
    driveLB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    driveLF.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    driveRB.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    driveRF.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    driveRM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    driveLM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  } //end of if, else if, else
} //end of setBrakeMode

//******************************************************************************
//
//SENSOR VALUES
//
//these functions return sensor values that are primarily used for autonomous
//programs and our PID controllers
//
//******************************************************************************

float avgDriveEncoderValue() {
  return (fabs(driveLF.get_position()) +
          fabs(driveLB.get_position()) +
          fabs(driveRF.get_position()) +
          fabs(driveRB.get_position()) +
          fabs(driveRM.get_position()) +
          fabs(driveLM.get_position())) / 6;
} //end of avgDriveEncoderValue

float inertialPitchValue() {
  return inertial_sensor.get_pitch();
} //end of inertialPitchValue

float inertialRollValue() {
  return inertial_sensor.get_roll();
} //end of inertialRollValue

float inertialRotationValue() {
  return inertial_sensor.get_rotation();
} //end of inertialRotationValue

int frontDistanceSensorValue() {
  return distF.get();
} //end of frontDistanceSensorValue

int backDistanceSensorValue() {
  return distB.get();
} //end of backDistanceSensorValue

float leftDriveEncoderValue() {
  return (fabs(driveLF.get_position()) +
          fabs(driveLB.get_position()) +
          fabs(driveLM.get_position())) / 3;
} //end of leftDriveEncoderValue

float rightDriveEncoderValue() {
  return (fabs(driveRF.get_position()) +
          fabs(driveRB.get_position()) +
          fabs(driveRM.get_position())) / 3;
} //end of rightDriveEncoderValue

//******************************************************************************
//
//DRIVE OPERATOR
//
//these functions operate the robot's chassis during the driver-control portion
//of the match
//
//******************************************************************************

void driveOPTankCurve() {
  int leftJoyStick, rightJoyStick, reversed = 1;
  setBrakeMode("COAST");
  leftJoyStick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  rightJoyStick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  //define direction
  int leftDirection = leftJoyStick / abs(leftJoyStick);
  int rightDirection = rightJoyStick / abs(rightJoyStick);
  //using exponential/curve drive, taking the square of joystick value over 127 to make precise movements at slow speeds
  int leftVoltage = (leftJoyStick * leftJoyStick) / 127;
  int rightVoltage = (rightJoyStick * rightJoyStick) / 127;
  //controller deadzone
  if (abs(leftVoltage) < 15) {leftVoltage = 0;} //end of if
  if (abs(rightVoltage) < 15) {rightVoltage = 0;} //end of if
  setDrive(leftVoltage * leftDirection, rightVoltage * rightDirection);
} //end of driveOPCurve

void driveOPTankReg() {
  int leftJoyStick, rightJoyStick, reversed = 1;
  setBrakeMode("COAST");
  leftJoyStick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  rightJoyStick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  int leftVoltage = leftJoyStick;
  int rightVoltage = rightJoyStick;
  //controller deadzone
  if (abs(leftVoltage) < 15) {leftVoltage = 0;} //end of if
  if (abs(rightVoltage) < 15) {rightVoltage = 0;} //end of if
  setDrive(leftVoltage, rightVoltage);
} //end of driveOPReg

void driveOPArcade() {
  setBrakeMode("COAST");
  int leftJoystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  //define direction
  int turnDirection = rightJoystick / abs(rightJoystick);
  int direction = leftJoystick / abs(leftJoystick);
  //using logarithmic drive, taking the square of joystick value over 127 to make precise movements at slow speeds
  int turnVoltage = rightJoystick;
  int voltage = (leftJoystick * leftJoystick) / 127;
  //controller deadzone
  if (abs(voltage) < 8) {voltage = 0;} //end of if
  if (abs(turnVoltage) < 8) {turnVoltage = 0;} //end of if
  int leftVoltage = (voltage * direction) + turnVoltage;
  int rightVoltage = (voltage * direction) - turnVoltage;
  setDrive(leftVoltage, rightVoltage);
} //end of driveOPArcade

//******************************************************************************
//
//AUTONOMOUS FUNCTIONS
//
//these functions are to be run during both the 15 second in game autonomous
//and the 1 minute skills autonomous portion
//
//******************************************************************************

//driving forward and backward with single-loop PID controller, setPoint is desired motor-encoder ticks (900 ticks per revolution)
void translate(int setPoint, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  //setting brake type based on parameter set
  setBrakeMode("COAST");
  //delta time, time between each interval
  const int deltaTime = 10;
  //establishing the time at which the function starts relative to the start of the program
  const int startTime = millis();
  //defining direction based on units provided
  const int direction = abs(setPoint)/setPoint; //either 1 or -1
  //resetting tracking wheel
  resetEncoder();
  //booleans
  bool robot_atTarget = false;
  bool robot_isAccelerating = true;
  //uncertainty for the movement (± tolerance)
  const float tolerance = 40;
  //inertial headings, used for self-correction
  float currHeading, headingError, headingDerivativeError, headingPrevError = 0, headingControl;
  const float imukP = 3;
  const float imukD = 10;
  const float headingTolerance = 2.5;
  //PID
  float error, sigmaError, derivativeError, prevError = abs(setPoint), processVariable, controlVariable;
  //the actual voltage being sent to the motors
  float voltage = 0;
  //string for displaying error on the brain screen
  string displayError;
  //dynamic array vectors for csv file
  vector<float> motorVoltage, elapsedTime, pid, process, setpoint;
  bool SDisInserted;
  if (pros::usd::is_installed() == 1) {SDisInserted = true;} //end of if
  //drive using single-loop PID controller until we are at the target
  float integralError;
  while(!robot_atTarget) {
    //heading of the robot in real time
    currHeading = inertialRotationValue();
    //amount of degrees robot has turned (used for self-correction)
    headingError = ((setHeading - currHeading) * -1);
    headingDerivativeError = (headingError - headingPrevError) / deltaTime;
    headingControl = (headingError * imukP) + (headingDerivativeError * imukD);
    //updating the process variable every time interval
    processVariable = abs(encoderValue()) / 40;
    //P term, proportional to the error
    error = abs(setPoint) - processVariable;
    //D term, rate of change of error
    derivativeError = (error - prevError) / deltaTime;
    //change in position on the robot from last iteration
    prevError = error;
    //using PD to give a voltage for the robot to move at
    controlVariable = (error * kP) + (derivativeError * kD);
    //Keeping track of error on the brain screen
    displayError = to_string(error);
    lcd::set_text(4, "Translate Error: " + displayError);
    //slew rate, accelerate at a constant rate until we hit max voltage parameter
    if (robot_isAccelerating) {
      voltage += slew;
      if (voltage > controlVariable || voltage > maxVoltage) {robot_isAccelerating = false;} //end of if
    } //end of if
    //Speed Control
    if (!robot_isAccelerating && controlVariable > maxVoltage) {voltage = maxVoltage;} //end of if
    //if the robot is not accelerating and we are starting to decelerate, activate "I" term and set the voltage to the PID
    if (!robot_isAccelerating && controlVariable < maxVoltage) {
      //I term, accumulated error
      sigmaError += error * deltaTime;
      //integral windUp limit
      if (sigmaError > windUp) {sigmaError = windUp;}
      //if we have overshot or error is 0, deactivate "I" term
      if (error <= 0) {kI = 0;} //end of if
      //using PID to give a voltage for the robot to move at
      controlVariable += (sigmaError * kI);
      //calculating new PID voltage after activating "I" term
      voltage = controlVariable;
    } //end of if
    //if conditions are met and we are at our target and moving slow, exit the while loop
    if (processVariable < abs(setPoint) + tolerance && processVariable > abs(setPoint) - tolerance) {
      if (fabs(driveLF.get_actual_velocity()) < fabs(voltage) + 35 && fabs(driveRF.get_actual_velocity()) < fabs(voltage) + 35) {
        if (currHeading < setHeading + headingTolerance && currHeading > setHeading - headingTolerance) {robot_atTarget = true;} //end of if
      } //end of if
    } //end of if
    //if this while loop takes more time than the max time specified above, exit the while loop
    if (millis() - startTime >= maxTime) {robot_atTarget = true;} //end of if
    //record data on microSD
    if (SDisInserted) {
      elapsedTime.push_back(millis() - startTime);
      motorVoltage.push_back(voltage);
      pid.push_back(controlVariable);
      process.push_back(processVariable);
      setpoint.push_back(setPoint);
    } //end of if
    //setting the voltage of the drive (based on trapezoidal motion profile)
    setDrive(voltage * direction - headingControl, voltage * direction + headingControl);
    //do not update too quickly
    delay(deltaTime);
} //end of PID while Loop
  //resetting PID & sensors, ending the function
  voltage = 0;
  setDrive(0,0);
  resetEncoder();
  //send data to microSD
  if (SDisInserted) {
    vector<pair<string, vector<float>>> translateData = {{"Elapsed Time", elapsedTime}, {"Process Variable", process}, {"Setpoint", setpoint}, {"Motor Voltage", motorVoltage}, {"PID Controller", pid}};
    write_csv("/usd/translateData.csv", translateData);
  } //end of if 
} //end of translate function

void translateDist(bool sensorType, int desiredDistance, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  int sensorValue, sensorValue1, sensorValue2;
  //determine which sensor to use based on input parameter
  if (sensorType) {
    sensorValue1 = frontDistanceSensorValue();
    delay(10);
    sensorValue2 = frontDistanceSensorValue();
    sensorValue = (sensorValue1 + sensorValue2) / 2;
  } else if (!sensorType) {
    sensorValue1 = backDistanceSensorValue();
    delay(10);
    sensorValue2 = backDistanceSensorValue();
    sensorValue = (sensorValue1 + sensorValue2) / 2;
  } //end of else if
  //calculate error
  int deltaDistance = sensorValue - desiredDistance;
  //factor label method to convert mm to motor encoder ticks
  int setPoint = deltaDistance * (1 / 25.4) * (1 / (3.25 * M_PI)) * 900 * (60 / 48);
  //reverse direction if necessary
  if (!sensorType) {setPoint *= -1;} //end of if
  translate(setPoint, setHeading, maxVoltage, slew, kP, kI, kD, windUp, maxTime);
} //end of translateDist function

//turning with a single-loop PID controller, setPoint is the desired heading angle (measured in degrees on unit circle)
void turnToHeading(float setPoint, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  resetDriveEncoders();
  //setting the brake type based on the parameter set
  setBrakeMode("COAST");
  //delta time, time between each interval
  const int deltaTime = 10;
  //minimum voltage needed to move base
  const int baseMotorPower = 10;
  //establishing the time at which the function starts relative to the start of the program
  const int startTime = millis();
  //defining a starting heading to determine which way to move
  float startHeading = inertialRotationValue() * 10;
  //multiplying the desired heading by 10, improving accuracy
  setPoint *= 10;
  //defining a direction based on units provided
  int direction;
  if (setPoint < startHeading) {direction = -1;} //end of if
  else {direction = 1;} //end of else
  //booleans
  bool robot_atTarget = false;
  bool robot_isAccelerating = true;
  //uncertainty for the rotate function, movements can range ±1 degrees
  const float tolerance = 15;
  //PID
  float error, sigmaError, derivativeError, prevError = (setPoint - startHeading) * direction, processVariable, controlVariable;
  //the actual voltage being sent to the motors
  float voltage = 0;
  //string for displaying error on the brain screen
  string displayError;
  //dynamic array vectors for csv file
  vector<float> motorVoltage, elapsedTime, pid, process, setpoint;
  bool SDisInserted;
  if (pros::usd::is_installed() == 1) {SDisInserted = true;} //end of if
  //drive using single-loop PID controller until we are at the target
  while(!robot_atTarget) {
    //determining the heading of the robot in real time
    processVariable = inertialRotationValue() * 10;
    //P term, proportional to the error
    error = (setPoint - processVariable) * direction;
    //D term, rate of change of error
    derivativeError = (error - prevError) / deltaTime;
    //change in position on the robot from last iteration
    prevError = error;
    //using PD to give a voltage for the robot to move at
    controlVariable = (error * kP) + (derivativeError * kD);
    //Keeping track of error on the brain screen
    displayError = to_string(error / 10);
    lcd::set_text(4, "Heading Error: " + displayError);
    //slew rate, accelerate at a constant rate until we hit max voltage parameter
    if (robot_isAccelerating) {
      voltage += slew;
      if (voltage > controlVariable || voltage > maxVoltage) {robot_isAccelerating = false;} // end of if
    } //end of if
    //Speed Control
    if (!robot_isAccelerating && controlVariable > maxVoltage) {voltage = maxVoltage;} //end of if
    //if the robot is not accelerating and we are starting to decelerate, activate "I" term and set the voltage to the PID
    if (!robot_isAccelerating && controlVariable < maxVoltage) {
      //I term, accumulated error
      sigmaError += error * deltaTime;
      //integral windUp limit
      if (sigmaError > windUp) {sigmaError = windUp;} //end of if
      //if we have overshot or error is 0, deactivate "I" term
      if (error <= 0) {kI = 0;} //end of if
      //using PID to give a voltage for the robot to move at
      controlVariable += (sigmaError * kI);
      //calculating new PID voltage after activating "I" term
      voltage = controlVariable;
    } //end of if
    //if conditions are met and we are at our target, exit the while loop
    if ((processVariable) < (setPoint) + tolerance && (processVariable) > (setPoint) - tolerance) {
      if (fabs(driveLF.get_actual_velocity()) < fabs(voltage) + 30 && fabs(driveRF.get_actual_velocity()) < fabs(voltage) + 30) {robot_atTarget = true;} //end of if
    } //end of if
    //if this while loop takes more time than the max time specified above, exit the while loop
    if (millis() - startTime >= maxTime) {robot_atTarget = true;} //end of if
    //record data on microSD
    if (SDisInserted) {
      elapsedTime.push_back(millis() - startTime);
      motorVoltage.push_back(voltage);
      pid.push_back(controlVariable);
      process.push_back(processVariable);
      setpoint.push_back(setPoint);
    } //end of if
    //setting the voltage of the drive (based on trapezoidal motion profile)
    setDrive(voltage * direction, -voltage * direction);
    //do not update too quickly
    delay(deltaTime);
} //end of PID while Loop
  //resetting PID & sensors, ending the function
  voltage = 0;
  setDrive(0,0);
  //send data to microSD
  if (SDisInserted) {
    vector<pair<string, vector<float>>> rotateData = {{"Elapsed Time", elapsedTime}, {"Process Variable", process}, {"Setpoint", setpoint}, {"Motor Voltage", motorVoltage}, {"PID Controller", pid}};
    write_csv("/usd/rotateData.csv", rotateData);
  } //end of if
} // end of turnToHeading function

//swing-turning with a single-loop PID controller, setPoint is the desired heading angle (measured in degrees on unit circle)
void swingToHeading(string baseSide, int setPoint, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  int leftSwing = 1;
  int rightSwing = 1;
  if (baseSide == "left") {rightSwing = 0;} //end of if
  else if (baseSide == "right") {leftSwing = 0;} //end of if
  resetDriveEncoders();
  //setting the brake type based on the parameter set
  setBrakeMode("COAST");
  //delta time, time between each interval
  const int deltaTime = 10;
  //establishing the time at which the function starts relative to the start of the program
  const int startTime = millis();
  //defining a starting heading to determine which way to move
  float startHeading = inertialRotationValue() * 10;
  //multiplying the desired heading by 10, improving accuracy
  setPoint *= 10;
  //defining a direction based on units provided
  int direction;
  if (setPoint < startHeading) {direction = -1;} //end of if
  else {direction = 1;} //end of else
  //booleans
  bool robot_atTarget = false;
  bool robot_isAccelerating = true;
  //uncertainty for the rotate function, movements can range ±1 degrees
  const float tolerance = 15;
  //PID
  float error, sigmaError, derivativeError, prevError = (setPoint - startHeading) * direction, processVariable, controlVariable;
  //the actual voltage being sent to the motors
  float voltage = 0;
  //string for displaying error on the brain screen
  string displayError;
  //dynamic array vectors for csv file
  vector<float> motorVoltage, elapsedTime, pid, process, setpoint;
  bool SDisInserted;
  if (pros::usd::is_installed() == 1) {SDisInserted = true;} //end of if
  //drive using single-loop PID controller until we are at the target
  while(!robot_atTarget) {
    //determining the heading of the robot in real time
    processVariable = inertialRotationValue() * 10;
    //P term, proportional to the error
    error = (setPoint - processVariable) * direction;
    //D term, rate of change of error
    derivativeError = (error - prevError) / deltaTime;
    //change in position on the robot from last iteration
    prevError = error;
    //using PD to give a voltage for the robot to move at
    controlVariable = (error * kP) + (derivativeError * kD);
    //Keeping track of error on the brain screen
    displayError = to_string(error);
    lcd::set_text(4, displayError);
    //slew rate, accelerate at a constant rate until we hit max voltage parameter
    if (robot_isAccelerating) {
      voltage += slew;
      if (voltage > controlVariable || voltage > maxVoltage) {
        robot_isAccelerating = false;
      } // end of if
    } //end of if
    //Speed Control
    if (!robot_isAccelerating && controlVariable > maxVoltage) {voltage = maxVoltage;} //end of if
    //if the robot is not accelerating and we are starting to decelerate, activate "I" term and set the voltage to the PID
    if (!robot_isAccelerating && controlVariable < maxVoltage) {
      //I term, accumulated error
      sigmaError += error * deltaTime;
      //integral windUp limit
      if (sigmaError > windUp) {sigmaError = windUp;} //end of if
      //if we have overshot or error is 0, deactivate "I" term
      if (error <= 0) {kI = 0;} //end of if
      //using PID to give a voltage for the robot to move at
      controlVariable += (sigmaError * kI);
      //calculating new PID voltage after activating "I" term
      voltage = controlVariable;
    } //end of if
    //if conditions are met and we are at our target, exit the while loop
    if (fabs(processVariable) < abs(setPoint) + tolerance && fabs(processVariable) > abs(setPoint) - tolerance) {
      if (fabs(driveLB.get_actual_velocity()) < fabs(voltage) + 30 && fabs(driveRB.get_actual_velocity()) < fabs(voltage) + 30) {robot_atTarget = true;} //end of if
    } //end of if
    //if this while loop takes more time than the max time specified above, exit the while loop
    if (millis() - startTime >= maxTime) {robot_atTarget = true;} //end of if
    //record data on microSD
    if (SDisInserted) {
      elapsedTime.push_back(millis() - startTime);
      motorVoltage.push_back(voltage);
      pid.push_back(controlVariable);
      process.push_back(processVariable);
      setpoint.push_back(setPoint);
    } //end of if
    //setting the voltage of the drive (based on trapezoidal motion profile)
    setDrive(((voltage * direction) * leftSwing), -((voltage * direction) * rightSwing));
    //do not update too quickly
    delay(deltaTime);
} //end of PID while Loop
  //resetting PID & sensors, ending the function
  voltage = 0;
  setDrive(0,0);
  //send data to microSD
  if (SDisInserted) {
    vector<pair<string, vector<float>>> swingData = {{"Elapsed Time", elapsedTime}, {"Process Variable", process}, {"Setpoint", setpoint}, {"Motor Voltage", motorVoltage}, {"PID Controller", pid}};
    write_csv("/usd/swingData.csv", swingData);
  } //end of if
} // end of swingToHeading function