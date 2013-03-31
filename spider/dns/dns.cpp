#include "dns.h"

Dns::Dns()
{
	pthread_mutex_init(&dnslock,NULL);
}

int Dns::GetHostInfo(string host,HOSTINFO &info)
{
	pthread_mutex_lock(&dnslock);
	
	struct addrinfo hints;
	struct addrinfo *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	int s = getaddrinfo(host.c_str(),"80",&hints
		,&result);
	if (s != 0) 
	{
	   LogError("getaddrinfo" + host);
	   pthread_mutex_unlock(&dnslock);
	   return -1;
	}
	
	info.ai_family = result->ai_family;
	info.ai_socktype = result->ai_socktype;
	info.ai_protocol = result->ai_protocol;
	info.ai_addrlen = result->ai_addrlen;
	memcpy(&info.ai_addr,result->ai_addr
		,sizeof(sockaddr));

	freeaddrinfo(result);
	
	pthread_mutex_unlock(&dnslock);
	return 0;
}