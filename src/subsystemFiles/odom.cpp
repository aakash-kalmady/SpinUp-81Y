#include "main.h"
#include <cmath>
#include <string>
using namespace pros;
using namespace std;
float robot_pos_x = 0;
float robot_pos_y = 0;

//odometry task
void trackPosition() {
  //diamater of tracking wheels in inches
  const float diamater = 2.75;
  //encoder ticks per revolution, Optical Shaft Encoders
  const float ticks_per_revolution = 36000;
  //inches per tick conversion
  const float inches_per_tick = (diamater * M_PI) / ticks_per_revolution;
  //previous position of each odometry encoder from the last time interval
  int prevEncoderPosition = 0;
  int prevAuxEncoderPosition = 0;
  //strings for displaying coordinates on LCD
  string robot_posX;
  string robot_posY;
  while (true) {
    //raw encoder values
    int encoderPosition = encoderValue();
    int encoderAuxPosition = encoderAuxValue();
    //change in position for odometer
    int deltaEncoderPosition = encoderPosition - prevEncoderPosition;
    int deltaAuxEncoderPosition = encoderAuxPosition - prevAuxEncoderPosition;
    //setting the previous encoder reading to the current encoder reading
    prevEncoderPosition = encoderPosition;
    prevAuxEncoderPosition = encoderAuxPosition;
    float theta = inertialRotationValue() * (M_PI/180);
    //calculating change in position, relative to the robots previous position
    float deltaX = inches_per_tick * (deltaAuxEncoderPosition * cos(theta) + deltaEncoderPosition * sin(theta));
    float deltaY = inches_per_tick * (deltaEncoderPosition * cos(theta) - deltaAuxEncoderPosition * sin(theta));
    //calculating realtive to field coordinate system
    robot_pos_x += deltaX;
    robot_pos_y += deltaY;
    //displaying on LCD
    robot_posX = to_string(robot_pos_x);
    robot_posY = to_string(robot_pos_y);
    lcd::set_text(6, "Pose: " + robot_posX + ", " + robot_posY);
    delay(10);
  } //end of while
} //end of trackPosition