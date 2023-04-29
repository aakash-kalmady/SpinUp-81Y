#include "main.h"
#include <string>
using namespace pros;
using namespace std;
//constants that define the geometry of the robot
//distance between encoder 1 and 2 in inches
const float L = 14.1;
//distance between the midpoint of encoder 1 and 2 and encoder 3 in inches
const float B = 7.2;
//diamater of tracking wheels in inches
const float diamater = 3;
//encoder ticks per revolution, Optical Shaft Encoders
const float ticks_per_revolution = 360;
const float inches_per_tick = (diamater * PI) / ticks_per_revolution;
//the current position of each odometry encoder every time interval
int rightPosition;
int leftPosition;
int auxPosition;
//previous position of each odometry encoder from the last time interval
int prevRightPosition = 0;
int prevLeftPosition = 0;
int prevAuxPosition = 0;
//position of robot
float robot_pos_x = 0;
float robot_pos_y = 0;
float robot_pos_hRad = 0; //heading
float robot_pos_h = 0; //heading
//strings for displaying coordinates on LCD
string robot_posX;
string robot_posY;
string robot_posH;

void odomTrackPosition() {
  /*
  //raw encoder values
  rightPosition = rightEncoderValue();
  leftPosition = leftEncoderValue();
  auxPosition = auxEncoderValue();
  //change in position for left odometer
  int deltaLeftPosition = leftPosition - prevLeftPosition;
  //change in position for right odometer
  int deltaRightPosition = rightPosition - prevRightPosition;
  //change in position for aux odometer
  int deltaAuxPosition = auxPosition - prevAuxPosition;
  //setting the previous encoder reading to the current encoder reading
  prevRightPosition = rightPosition;
  prevLeftPosition = leftPosition;
  prevAuxPosition = auxPosition;
  //calculating change in position, relative to the robots previous position
  float deltaThetaRad = inches_per_tick * (deltaLeftPosition - deltaRightPosition) / L;
  float deltaThetaDeg = deltaThetaRad * 180 / PI;
  float deltaX = inches_per_tick * (deltaAuxPosition - (deltaLeftPosition - deltaRightPosition) * B / L );
  float deltaY = inches_per_tick * (deltaLeftPosition + deltaRightPosition) / 2;
  //calculating realtive to field coordinate system
  float theta = robot_pos_hRad + (-deltaThetaRad / 2);
  robot_pos_x += deltaX * cos(theta) - deltaY * sin(theta);
  robot_pos_y += deltaX * sin(theta) + deltaY * cos(theta);
  robot_pos_hRad += deltaThetaRad;
  robot_pos_h += deltaThetaDeg;
  //displaying on LCD
  robot_posX = to_string(robot_pos_x);
  robot_posY = to_string(robot_pos_y);
  robot_posH = to_string(robot_pos_h);
  lcd::set_text(1, robot_posX);
  lcd::set_text(2, robot_posY);
  lcd::set_text(3, robot_posH);
  */
} //end of trackPosition


void moveTo(float x, float y, float heading, int driveMaxVoltage, int turnMaxVoltage, int driveSlew, int turnSlew, float drivekP, float drivekI, float drivekD, float turnkP, float turnkI, float turnkD, float driveWindUp, float turnWindUp, int driveMaxTime, int turnMaxTime) {
  //getting robot's absolute position
  c::gps_status_s_t gpsData;
  gpsData = gps1.get_status();
  //calculating the change in x and y that is necessary to get to the new coordinate
  float deltaX = x - (gpsData.x);
  float deltaY = y - (gpsData.y);
  //calculating the heading that is necessary to face the new coordinate
  float lookAheadHeading = (atan(deltaX/deltaY)) * (180/PI);

  if (sign(deltaX) == -1 && sign(deltaY) == -1) {
    lookAheadHeading -= 180;
  } else if (sign(deltaX) == 1 && sign(deltaY) == -1) {
    lookAheadHeading += 180;
  } //end of else if

  //distance formula
  float distance = sqrt((deltaX*deltaX) + (deltaY*deltaY));
  //converting distance to motor encoder ticks
  distance *= 39.37; //meters to inches
  float translateDistance = (((distance / (3.25 * PI))) * 3/5) * 900; //inches to ticks
  //robot movement
  turnToHeading(lookAheadHeading, turnMaxVoltage, turnSlew, turnkP, turnkI, turnkD, turnWindUp, turnMaxTime);
  translate(translateDistance, lookAheadHeading, driveMaxVoltage, driveSlew, drivekP, drivekI, drivekD, driveWindUp, driveMaxTime);
  turnToHeading(heading, turnMaxVoltage, turnSlew, turnkP, turnkI, turnkD, turnWindUp, turnMaxTime);
} //end of move to
