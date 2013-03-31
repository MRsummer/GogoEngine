#include "core.h"

Dns *dns;
Pool *pool;
struct epoll_event rev,revents[MAXEVENTS];
struct epoll_event wev,wevents[MAXEVENTS];
int repollfd,wepollfd;
Regx * pregx;

void InitSpider()
{
	//init the dns server
	dns = new Dns();
	
	//init url pool (url manager)
	pool = new Pool();
	
	//create epool fd
	repollfd = epoll_create(MAXEVENTS);
	wepollfd = epoll_create(MAXEVENTS);
	if(repollfd == -1 || wepollfd == -1)
	{
		PrintErrorAndExit("epoll_create");
	}
	
	//create regx expression (match url)
	pregx = new Regx("<a[^>]*href=[\'\"]"
		"([^>]+)[\'\"][^>]*>[^<]*</a>");
}

void StopSpider()
{
	delete dns;
	delete pool;
}

void StartSpider()
{
	pthread_t pid[THREADNUM];
	for(int i=0;i < THREADNUM;i ++)
	{
		pthread_create(&pid[i],NULL,threadfun
			,NULL);
	}
}

void * threadfun(void *arg)
{
	Run();
}

void Run()
{
	for(int i = 0;i < 10;i ++)
	{
		int sockfd;
		HOSTINFO info;
		
		//get url from pool
		string url = pool->GetUrl();
		string host = GetHostByUrl(url);
		
		//get host addrinfo from net
		if(dns->GetHostInfo(host,info) == -1)
		{
			PrintError("GetHostInfo");
			continue;
		}
		
		//try to connect with the server
		if(TryConnect(&info,sockfd) == -1)
		{
			PrintError("TryConnect");
			continue;
		}
		
		//new a EPOLLARG
		EPOLLARG *parg = new EPOLLARG();		
		parg->sockfd = sockfd;
		memset(parg->url,0,URLLEN);
		strcpy(parg->url,url.c_str());
		
		//add to epoll write control
		wev.events = EPOLLOUT;
		wev.data.ptr = (void*)parg;
		if (epoll_ctl(wepollfd, EPOLL_CTL_ADD
			,sockfd,&wev) == -1) 
		{
		   PrintError("epoll_ctl add");
		   continue;
		}
	}
	
	//epoll wait the sockfds to be writable
	int wnfds = epoll_wait(wepollfd,wevents
		,MAXEVENTS,WRITEWAITTIME);
		
	for(int i = 0;i < wnfds;i ++)
	{
		//get epoll arg
		EPOLLARG *parg = (EPOLLARG*)wevents[i].data.ptr;
		int sockfd = parg->sockfd;
		string url = parg->url;
		string host = GetHostByUrl(url);
		string resource = GetResourceByUrl(url);
		
		//write http request
		WriteHttpRequest(host,resource,sockfd);
		
		//delete epoll write control
		if(epoll_ctl(wepollfd,EPOLL_CTL_DEL
			,sockfd,NULL) == -1)
		{
			PrintError("epoll_ctl del");
			continue;
		}
		
		//add to epoll read control
		rev.events = EPOLLIN;
		rev.data.ptr = (void*)parg;
		if(epoll_ctl(repollfd,EPOLL_CTL_ADD
			,sockfd,&rev) == -1)
		{
			PrintError("epoll_ctl add");
			continue;
		}
	}
	
	//epoll wait the sockfds to be readable
	int rnfds = epoll_wait(repollfd,revents
		,MAXEVENTS,READWAITTIME);
		
	for(int i = 0;i < rnfds;i ++)
	{
		//add epoll arg
		EPOLLARG *parg = (EPOLLARG*)revents[i].data.ptr;
		int sockfd = parg->sockfd;
		string url = parg->url;
		string host = GetHostByUrl(url);
		delete(parg);
		
		//read content
		string content = ReadContent(sockfd);
		
		//save content
		ReplaceChar(url,'/','_');
		File file = File("../doc/"+url,"w");
		file.WriteContent(content);
		file.Close();
		
		//get all urls
		vector<string> urls;
		pregx->Match(content.c_str(),urls,1);
		
		//add url to pool
		for(int i = 0;i < urls.size();i ++)
		{
			string url = ProcessUrl(urls[i],host);
			if(url != "")
				pool->AddUrl(url);
		}
	}//end of process
}
