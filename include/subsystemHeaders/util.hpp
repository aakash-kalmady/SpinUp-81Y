#ifndef _UTIL_H_
#define _UTIL_H_
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include "main.h"
using namespace pros;
using namespace std;

/*
* @array of all timers
*/
// extern int timer[10];
//
// enum TimerName {
//   BALL
// } TimerName_t;

/*
* @func: Clears all the lines on the LCD screen
*/
extern void clearLCDLines();

/*
* @func: Determines the sign of an input number
*   @param: The input number
*   @return: 1 or -1
*/
extern float sign(float input);

/*
* @func: Corrects the sign of a number to a number of a different sign
*   @param: The input number
*   @param: The same sign number
*/
extern float signChecker(float input, float sameSign);

/*
* @func: Limits the input to a max number
*   @float: The input number
*   @float: The maximum number
*   @return: input or max number
*/
extern float limit(float input, float max);

/*
* @func: Inserts a csv file with a header row,
*   and then columns and rows of numbers in the Micro SD Card
*   @string: The file name
*   @param: The headers with the appropiate column and rows
*/
extern void write_csv(string filename,
  vector<pair<string, vector<float>>> dataset);

/*
* @func: Reads a csv file with a header row,
*   and then columns and rows of numbers in the Micro SD Card
*   @string: The file name
*/
extern vector<pair<string, vector<int>>>
  read_csv(string filename);

#endif
