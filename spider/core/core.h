/***********************************************
*the core logic spider using epoll structure
*author : summer  2013/3/23
************************************************/
#ifndef CORE_H_
#define CORE_H_

#include <sys/epoll.h>
#include <pthread.h>
#include <string.h>

#include "../../common/file/file.h"
#include "../../common/regx/regx.h"
#include "../../common/url/url.h"
#include "../../common/net/net.h"
#include "../../common/str/str.h"
#include "../dns/dns.h"
#include "../pool/pool.h"

#include <string>
#include <algorithm>
using namespace std;

//thread property
#define THREADNUM 1
//epoll property
#define MAXEVENTS 20
#define READWAITTIME 10
#define WRITEWAITTIME 10

#define URLLEN 1024
typedef struct{
	char url[URLLEN];
	int sockfd;
}EPOLLARG;

void InitSpider();
void StartSpider();
void StopSpider();
void * threadfun(void *arg);
void Run();

#endif /*CORE_H_*/
