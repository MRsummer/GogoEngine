#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in in;
	memset(&in,0,sizeof(in));
	in.sin_family = AF_INET;
	inet_pton(AF_INET,"202.114.18.14",&in.sin_addr);
	in.sin_port = htons(80);
	connect(sockfd,(struct sockaddr *)&in,sizeof(in));

	char request[1024] = {"GET /seek HTTP/1.1\r\nHost: ershou.hustonline.net\r\n\r\n"};
	write(sockfd,request,strlen(request));
	char request1[1024] = {"GET / HTTP/1.0\r\nHOST:pic.hustonline.net\r\n\r\n"};
	write(sockfd,request1,strlen(request1)+1);
	char request2[1024] = {"GET / HTTP/1.0\r\nHOST:www.hustonline.net\r\n\r\n"};
	write(sockfd,request2,strlen(request2)+1);

	char buff[1024] = {0};
	while(read(sockfd,buff,1024) > 0)
	{
		printf("%s",buff);
		memset(buff,0,1024);
	}

	return 0;
}
