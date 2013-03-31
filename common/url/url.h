/************************************************
*basic url functions
*author : summer 2013/3/23
************************************************/

#ifndef URL_H_
#define URL_H_

#include <string>

using namespace std;

string ProcessUrl(string urlstr,string host);
string GetHostByUrl(string url);
string GetResourceByUrl(string url);

#endif /*URL_H_*/
