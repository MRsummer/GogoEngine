/***************************************************
*basic regex operation,match what you want
*author : summer 2013/3/22
***************************************************/

#ifndef REGX_H_
#define REGX_H_

#include <regex.h>

#include <string>
#include <vector>

#include "../error/error.h"

using std::string;
using std::vector;

class Regx
{
public:
	//compile the pattern
	Regx(string pattern);
	//release the regex object
	~Regx();
	//match all the content and return a vector
	int Match(string content,vector<string> &v
		,int patternIndex);
	//just match the first pattern
	string MatchOnce(string content
		,int patternIndex);
private:
	regex_t preg;
};

#endif /*REGX_H_*/
