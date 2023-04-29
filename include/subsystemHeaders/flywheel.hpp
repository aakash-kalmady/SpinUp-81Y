#include "main.h"
#include <string>
using namespace pros;
using namespace std;
extern int shootingVoltage;
extern bool shooting;

//HELPER FUNCTIONS
extern void setFlywheel(int power);

//VALUES
extern int shotTrackerValue();

//DRIVER CONTROL FUNCTIONS
extern void flywheelOP();

//AUTONOMOUS FUNCTIONS
extern void shoot();
extern void farMode(int target);
extern void closeMode();
extern void middleMode(int target);