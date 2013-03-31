/************************************************
*a simple pool that manage all the urls
*author : summer  2013/3/23
************************************************/
#ifndef POOL_H_
#define POOL_H_

#include <map>
#include <string>
#include <iostream>
#include <queue>

#include <pthread.h>
#include <string.h>

#include "../../common/url/url.h"

using namespace std;

//the struct to keep url information
typedef struct{
	int crawed;
	int level;
	int score;
}URLINFO;
//urls under a host
typedef map<string,URLINFO> URLMAP;
//hosts map
typedef map<string,URLMAP*> HOSTMAP;
//url target queue
typedef queue<string> URLQUEUE;
//url black list
typedef map<string,int> BLACKURLMAP;

class Pool
{
public:
	//construct method
	Pool();
	//store pool and destroy urlmap
	~Pool();
	void AddUrl(string url);
	string GetUrl();
	void AddTargetUrl(string url);
	void PrintPool();
private:
	//map that contains host
	HOSTMAP hostmap;
	//the default url target queue,fast
	URLQUEUE urlqueue;
	//the slow url queue,when get the url 
	//failed,add to slow url queue
	URLQUEUE slowurlqueue;
	//when failed to get the url in slow url 
	//queue,add it to black list
	BLACKURLMAP blackurlmap;
	
	pthread_mutex_t lock;
};

#endif /*POOL_H_*/
