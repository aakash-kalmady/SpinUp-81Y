#include "main.h"
#include <string>
using namespace pros;
using namespace std;

//******************************************************************************
//
//HELPER FUNCTIONS
//
//these functions are to be used both during driver control and autonomous
//to simplify the code. setDrive sets the voltage of the drive train.
//resetDriveEncoders() resets the sensor values for the motor encoders.
//resetOdomEncoders() resets the sensor values for the odometry.
//setBrakeType sets the brakemode for the drivetrain.
//
//******************************************************************************

void setDrive(int left, int right) {
  driveLF = left;
  driveLM = left;
  driveRF = right;
  driveLB = left;
  driveRB = right;
  driveRM = right;
} //end of setDrive

void resetDriveEncoders() {
  driveLB.tare_position();
  driveLF.tare_position();
  driveRB.tare_position();
  driveRF.tare_position();
  driveRM.tare_position();
  driveLM.tare_position();
} //end of resetDriveEncoders

void resetOdomEncoders() {
  encoderRight.reset();
  encoderLeft.reset();
  encoderAux.reset();
} //end of resetOdomEncoders

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
  }
} //end of setBrakeMode

//******************************************************************************
//
//SENSOR VALUES
//
//these sensor values are primarily used for our single-loop PID controllers
//avgDriveEncoderValue() takes the average of all 4 motor encoders to give us
//the robots current position
//inertialRotationValue() gives us the current heading of the robot relative to
//the start of the program, and uses the average of two sensors
//distanceSensorValue() gives us the distance the robot is away from the fence
//avgEncoderValue() gives us the average of the odom encoders in the y-direction
//left, right, and aux encoder value gives us the individual odom encoder values
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

float inertialRotationValue() {
  return inertial_sensor.get_rotation();
} //end of inertialRotationValue

float inertialRollValue() {
  return inertial_sensor.get_roll();
} //end of inertialRotationValue

float inertialPitchValue() {
  return inertial_sensor.get_pitch();
} //end of inertialRotationValue

float gpsRotationValue() {
  return gps1.get_rotation();
} //end of gpsRotationValue

float frontDistanceSensorValue() {
  return distF.get();
} //end of inertialRotationValue

float backDistanceSensorValue() {
  return distB.get();
} //end of inertialRotationValue

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
//this function controls the robot's chassis during the driving portion of
//the match
//
//******************************************************************************

void driveOP() {
  setBrakeMode("COAST");
  //raw joystick values
  int leftJoystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  //direction
  int leftDirection = leftJoystick / abs(leftJoystick);
  int rightDirection = rightJoystick / abs(rightJoystick);
  //using logarithmic drive, taking the square of joystick value over 127 to make precise movments at slow speeds
  int leftVoltage = (leftJoystick * leftJoystick) / 127;
  int rightVoltage = (rightJoystick * rightJoystick) / 127;
  //controller deadzone
  if (abs(leftVoltage) < 10) {
    leftVoltage = 0;
  } //end of if
  if (abs(rightVoltage) < 10) {
    rightVoltage = 0;
  } //end of if
  setDrive(leftVoltage * leftDirection, rightVoltage * rightDirection);
} //end of chassisOP

//******************************************************************************
//
//AUTONOMOUS FUNCTIONS
//
//these functions are to be run during both the 15 second in game autonomous
//and the 1 minute skills autonomous portion
//translate moves the robot forward/backward with shaft encoders
//driveWithDistance moves the robot to a certain distance from the fence
//turnToHeading uses inretial sensor to turn the robot to a desired heading
//
//******************************************************************************

//driving forward and backward with single-loop PID controller, setPoint is desired motor-encoder ticks (900 ticks per revolution)
void translate(float setPoint, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  //setting brake type based on paramater set
  setBrakeMode("COAST");
  //delta time, time between each interval
  const int deltaTime = 10;
  //establishing the time at which the function starts relative to the start of the program
  const int startTime = millis();
  //defining direction based on units provided
  const int direction = sign(setPoint); //either 1 or -1
  //resetting motor encoders
  resetDriveEncoders();
  //booleans
  bool robot_atTarget = false;
  bool robot_isAccelerating = true;
  //uncertainty for the movement (± tolerance)
  const float tolerance = 80;
  //inertial headings, used for self-correction
  float currHeading, headingError, headingDerivativeError, headingPrevError = 0, headingControl;
  const float imukP = 5;
  const float imukD = 2;
  const float headingTolerance = 0.5;
  //PID
  float error, sigmaError, derivativeError, prevError = setPoint, processVariable, controlVariable;
  //the actual voltage being sent to the motors
  float voltage = 0;
  //string for displaying error on the brain screen
  string displayError;
  //dynamic array vectors for csv file
  vector<float> motorVoltage, elapsedTime, pid, process, setpoint;
  bool SDisInserted;
  if (pros::usd::is_installed() == 1) {
    SDisInserted = true;
  } //end of if
  //drive using single-loop PID controller until we are at the target
  while(!robot_atTarget) {
    //heading of the robot in real time
    currHeading = inertialRotationValue();
    //amount of degrees robot has turned (used for self-correction)
    headingError = ((setHeading - currHeading) * -1);
    headingDerivativeError = (headingError - headingPrevError) / deltaTime;
    headingControl = (headingError * imukP) + (headingDerivativeError * imukD);
    //updating the process variable every time interval
    processVariable = avgDriveEncoderValue();
    //P term, proportinal to the error
    error = abs(setPoint) - processVariable;
    //D term, rate of change of error
    derivativeError = (error - prevError) / deltaTime;
    //change in position on the robot from last itteration
    prevError = error;
    //using PD to give a voltage for the robot to move at
    controlVariable = (error * kP) + (derivativeError * kD);
    //Keeping track of error on the brain screen
    displayError = to_string(error);
    lcd::set_text(4, displayError);
    //slew rate, accelerate at a constant rate untill we hit max voltage paramater
    if (robot_isAccelerating) {
      voltage += slew;
      if (voltage > controlVariable || voltage > maxVoltage) {
        robot_isAccelerating = false;
      } // end of if
    } //end of if
    //Speed Control
    if (!robot_isAccelerating && controlVariable > maxVoltage) {
        voltage = maxVoltage;
      } //end of if
    //if the robot is not accelerating and we are starting to decelerate, activate "I" term and set the voltage to the PID
    if (!robot_isAccelerating && controlVariable < maxVoltage) {
      //I term, accumulated error
      sigmaError += error * deltaTime;
      //integral windUp limit
      if (sigmaError > windUp) {
        sigmaError = windUp;
      } //end of if
      //if we have overshot or error is 0, deactivate "I" term
      if (error <= 0) {
        kI = 0;
      } //end of if
      //using PID to give a voltage for the robot to move at
      controlVariable += (sigmaError * kI);
      //calculating new PID voltage after activating "I" term
      voltage = controlVariable;
    } //end of if
    //if conditions are met and we are at our target and moving slow, exit the while loop
    if (processVariable < abs(setPoint) + tolerance && processVariable > abs(setPoint) - tolerance) {
      if (driveLB.get_actual_velocity() < abs(voltage) + 5 && driveRB.get_actual_velocity() < abs(voltage) + 5) {
        if (headingError < headingTolerance && headingError > -headingTolerance) {
          robot_atTarget = true;
        } //end of if
      } //end of if
    } //end of if
    //if this while loop takes more time than the max time specified above, exit the while loop
    if (millis() - startTime >= maxTime) {
        robot_atTarget = true;
      } //end of if
    //record data on microSD
    if (SDisInserted) {
      elapsedTime.push_back(millis() - startTime);
      motorVoltage.push_back(voltage);
      pid.push_back(controlVariable);
      process.push_back(processVariable);
      setpoint.push_back(setPoint);
    } //end of if
    //setting the voltage of the drive (based on trapeziodal motion profile)
    setDrive(voltage * direction - headingControl, voltage * direction + headingControl);
    //dont update too quickly
    delay(deltaTime);
} //end of PID while Loop
  //reseting PID & sensors, ending the function
  voltage = 0;
  resetDriveEncoders();
  //send data to microSD
  if (SDisInserted) {
    vector<pair<string, vector<float>>> translateData = {{"Elapsed Time", elapsedTime}, {"Process Variable", process}, {"Setpoint", setpoint}, {"Motor Voltage", motorVoltage}, {"PID Controller", pid}};
    write_csv("/usd/translateData.csv", translateData);
  } //end of if
} //end of translate function

void translateDist(bool sensorType, float desiredDistance, float setHeading, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  float sensorValue;
  if (sensorType) {
    sensorValue = distF.get();
    delay(10);
    sensorValue = distF.get();
  } else if (!sensorType) {
    sensorValue = distB.get();
    delay(10);
    sensorValue = distB.get();
  }
  float deltaDistance = sensorValue - desiredDistance;
  float setPoint = deltaDistance * (1 / 25.4) * (1 / 10.2102) * (900) * 3/5;
  if (!sensorType) {
    setPoint *= -1;
  }
  translate(setPoint, setHeading, maxVoltage, slew, kP, kI, kD, windUp, maxTime);

} //end of translateDist

//turning with a single-loop PID controller, setPoint is the desired heading angle (measured in degrees on unit circle)
void turnToHeading(float setPoint, int maxVoltage, int slew, float kP, float kI, float kD, float windUp, int maxTime) {
  resetDriveEncoders();
  //setting the brake type based on the paramater set
  setBrakeMode("COAST");
  //delta time, time between each interval
  const int deltaTime = 10;
  //miminum voltage needed to move base
  const int baseMotorPower = 13;
  //establishing the time at which the function starts relative to the start of the program
  const int startTime = millis();
  //defining a starting heading to determine which way to move
  float startHeading = inertialRotationValue() * 10;
  //multiplying the desired heading by 10, improving accuracy
  setPoint *= 10;
  //defining a direction based on units provided
  int direction;
  if (setPoint < startHeading) {
      direction = -1;
  } else {
      direction = 1;
  } //end of if else
  //booleans
  bool robot_atTarget = false;
  bool robot_isAccelerating = true;
  //uncertainty for the rotate function, movements can range ±1 degrees
  const float tolerance = 25;
  //correction for turning about robots center
  float leftCorrection = 0, rightCorrection = 0;
  //PID
  float error, sigmaError, derivativeError, prevError = (setPoint - startHeading) * direction, processVariable, controlVariable;
  //the actual voltage being sent to the motors
  float voltage = 0;
  //string for displaying error on the brain screen
  string displayError;
  //dynamic array vectors for csv file
  vector<float> motorVoltage, elapsedTime, pid, process, setpoint;
  bool SDisInserted;
  if (pros::usd::is_installed() == 1) {
    SDisInserted = true;
  } //end of if
  //drive using single-loop PID controller until we are at the target
  while(!robot_atTarget) {
    //determining the heading of the robot in real time
    processVariable = inertialRotationValue() * 10;
    //P term, proportinal to the error
    error = (setPoint - processVariable) * direction;
    //D term, rate of change of error
    derivativeError = (error - prevError) / deltaTime;
    //change in position on the robot from last itteration
    prevError = error;
    //using PD to give a voltage for the robot to move at
    controlVariable = (error * kP) + (derivativeError * kD);
    //Keeping track of error on the brain screen
    displayError = to_string(error);
    lcd::set_text(4, displayError);
    //slew rate, accelerate at a constant rate untill we hit max voltage paramater
    if (robot_isAccelerating) {
      voltage += slew;
      if (voltage > controlVariable || voltage > maxVoltage) {
        robot_isAccelerating = false;
      } // end of if
    } //end of if
    //Speed Control
    if (!robot_isAccelerating && controlVariable > maxVoltage) {
        voltage = maxVoltage;
      } //end of if
    //if the robot is not accelerating and we are starting to decelerate, activate "I" term and set the voltage to the PID
    if (!robot_isAccelerating && controlVariable < maxVoltage) {
      //I term, accumulated error
      sigmaError += error * deltaTime;
      //integral windUp limit
      if (sigmaError > windUp) {
        sigmaError = windUp;
      } //end of if
      //if we have overshot or error is 0, deactivate "I" term
      if (error <= 0) {
        kI = 0;
      } //end of if
      //using PID to give a voltage for the robot to move at
      controlVariable += (sigmaError * kI);
      //calculating new PID voltage after activating "I" term
      voltage = controlVariable;
    } //end of if
    if (leftDriveEncoderValue() < rightDriveEncoderValue()) {
      leftCorrection = rightDriveEncoderValue() - leftDriveEncoderValue();
      leftCorrection *= 0.7;
    }
    if (rightDriveEncoderValue() < leftDriveEncoderValue()) {
      rightCorrection = leftDriveEncoderValue() - rightDriveEncoderValue();
      rightCorrection *= 0.7;
    }
    //if conditions are met and we are at our target, exit the while loop
    if (fabs(processVariable) < fabs(setPoint) + tolerance && fabs(processVariable) > fabs(setPoint) - tolerance) {
      if (fabs(driveLB.get_actual_velocity()) < abs(voltage) + 5 && fabs(driveRB.get_actual_velocity()) < abs(voltage) + 5) {
        robot_atTarget = true;
      } //end of if
    } //end of if
    //if this while loop takes more time than the max time specified above, exit the while loop
    if (millis() - startTime >= maxTime) {
        robot_atTarget = true;
      } //end of if
    //record data on microSD
    if (SDisInserted) {
      elapsedTime.push_back(millis() - startTime);
      motorVoltage.push_back(voltage);
      pid.push_back(controlVariable);
      process.push_back(processVariable);
      setpoint.push_back(setPoint);
    } //end of if
    //setting the voltage of the drive (based on trapeziodal motion profile)
    setDrive((voltage + leftCorrection) * direction, -(voltage + rightCorrection) * direction);
    //dont update too quickly
    delay(deltaTime);
} //end of PID while Loop
  //reseting PID & sensors, ending the function
  voltage = 0;
  setDrive(0,0);
  //send data to microSD
  if (SDisInserted) {
    vector<pair<string, vector<float>>> rotateData = {{"Elapsed Time", elapsedTime}, {"Process Variable", process}, {"Setpoint", setpoint}, {"Motor Voltage", motorVoltage}, {"PID Controller", pid}};
    write_csv("/usd/rotate2Data.csv", rotateData);
  } //end of if
} // end of rotate function
