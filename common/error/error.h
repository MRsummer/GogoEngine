/*******************************************************
*common error functions
*author:summer 2013/3/22
*******************************************************/

#ifndef ERROR_H_
#define ERROR_H_

//c headers
#include <errno.h>
#include <string.h>

//c++ headers
#include <iostream>

//local headers
#include "../file/file.h"

//error file
#define ERRORFILE "error.log"

using namespace std;

void Print(string msg);
void PrintError(string msg);
void LogError(string msg);
void PrintAndExit(string msg);
void PrintErrorAndExit(string msg);
void LogErrorAndExit(string msg);

#endif /*ERROR_H_*/
