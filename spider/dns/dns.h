/************************************************
*a simple local dns
*author : summer 2013/3/23
************************************************/

#ifndef DNS_H_
#define DNS_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

#include <string>

#include "../../common/error/error.h"

using namespace std;

typedef struct{
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	size_t ai_addrlen;
	//in struct addrinfo,sockaddr is a pointer
	//so we have to change it to a nonpointer
	sockaddr ai_addr;
}HOSTINFO;

class Dns
{
public:
	Dns();
	int GetHostInfo(string host,HOSTINFO &info);
private:	
	pthread_mutex_t dnslock;
};

#endif /*DNS_H_*/
