/**********************************************
*basic network funcitons
*author : summer  2013/3/23
***********************************************/

#ifndef NET_H_
#define NET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <string>

#include "../../spider/dns/dns.h"
#include "../error/error.h"

using namespace std;

void SetNonBlocking(int sockfd);
int TryConnect(HOSTINFO *info,int &sockfd);
int WriteHttpRequest(string host,string resource,
	int sockfd);
string ReadContent(int sockfd);

#endif /*NET_H_*/
