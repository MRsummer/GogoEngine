/************************************************
*basic directory functions
*author : summer  2013/3/24
************************************************/

#ifndef DIR_H_
#define DIR_H_

#include <dirent.h>

#include <string>
#include <vector>

using namespace std;

void ListFiles(string path,vector<string> &files);

#endif /*DIR_H_*/