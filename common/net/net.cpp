/************************************************
*basic network funcitons 
*author : summer   2013/3/27
************************************************/
#include "net.h"

void SetNonBlocking(int sockfd)
{
	//not very clear here
	int b_on = 1;
	ioctl (sockfd,FIONBIO,&b_on);
}

int TryConnect(HOSTINFO *info,int &sockfd)
{
	sockfd = socket(info->ai_family
		,info->ai_socktype,info->ai_protocol);
	if(sockfd == -1)
	{
		return -1;
	}
	if(connect(sockfd,&info->ai_addr
		,info->ai_addrlen) != -1)
	{
	   return 0;
	}
	else if(errno == EINPROGRESS)
	{
		//find what is the problem here
		return 0;
	}
	else
	{
		return -1;
	}
}

int WriteHttpRequest(string host,string resource
	,int sockfd)
{
	string request = "GET " + resource 
		+ " HTTP/1.0\r\nHost: "+ host +"\r\n\r\n";
	if(write(sockfd,request.c_str()
		,request.length()+1) == -1)
	{
		LogError("write "+host+resource);
		return -1;
	}
	return 0;
}

string ReadContent(int sockfd)
{
	string content = "";
	char buf[BUFFERSIZE] = {0};
	while(read(sockfd,buf,BUFFERSIZE) > 0)
	{
		content += buf;
		memset(buf,0,BUFFERSIZE);
	}
	return content;
}
