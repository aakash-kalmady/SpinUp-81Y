#include "main.h"
#include <string>
using namespace pros;
using namespace std;

/*
* @func: Autonomous Selector
*   @param: The auton int generated from limit switch and auton selector
*/
extern void autonHandler(int auton);
/*
* @func: testing autonomous program
*/
extern void experimental();
/*
* @func: 8 disc win point autonomous program
*/
extern void leftWP();
/*
* @func: 6 disc right side autonomous program
*/
extern void right();
/*
* @func: 8 disc right side high risk autonomous program
*/
extern void rightRisk();
/*
* @func: skills autonomous program
*/
extern void skills();
/*
* @func: 8 disc left side autonomous program
*/
extern void leftRisk();
/*
* @func: 7 disc left side autonomous program
*/
extern void left();