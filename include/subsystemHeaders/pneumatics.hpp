#include "main.h"
#include <string>
using namespace pros;
using namespace std;

//VARIABLEs
extern bool angleShift_status;

//DRIVER CONTROL
extern void expansionOP();
extern void angleShifterOP();
extern void intakeTensionOP();

//AUTONOMOUS FUNCTIONS
extern void expand();
extern void angleShiftUp();
extern void angleShiftDown();
extern void discTensionRelease();
extern void discTensionEngage();
extern void intakeLift();
extern void intakeDown();