/************************************************
*open source lib:scws
*chinese word segment
*from: http://www.xunsearch.com/scws/docs.php
*modified by : summer 2013/3/24
************************************************/

#ifndef SCWS_H_
#define SCWS_H_

#include <stdio.h>
#include <scws/scws.h>
#define SCWS_PREFIX "/usr/local/scws"

#include <vector>
#include <string>

typedef struct{
	string word;
	int weight;
}SCWSRESULT;

using namespace std;

class Scws
{
public:
	Scws();
	void GetResult(string content
		,vector<SCWSRESULT> &v);
private:
	scws_t s;
};

#endif /*SCWS_H_*/