#include "pool.h"

Pool::Pool()
{
	pthread_mutex_lock(&lock);
}

Pool::~Pool()
{
	for(HOSTMAP::iterator it = hostmap.begin();
		it != hostmap.end(); ++ it)
	{
		URLMAP *purlmap = it->second;
		delete(purlmap);
	}
}

void Pool::AddUrl(string url)
{
	pthread_mutex_lock(&lock);
	
	string host = GetHostByUrl(url);
	HOSTMAP::iterator it = hostmap.find(host);
	if(it == hostmap.end())
	{
		//host not in hostmap
		URLINFO info;
		memset(&info,0,sizeof(URLINFO));
		URLMAP *purlmap = new URLMAP();
		purlmap->insert(URLMAP::value_type
			(url,info));
		hostmap.insert(HOSTMAP::value_type
			(host,purlmap));
	}
	else
	{
		//host in hostmap
		URLMAP *purlmap = it->second;
		if(purlmap->find(url) == purlmap->end())
		{
			//url not in urlmap
			URLINFO info;
			memset(&info,0,sizeof(URLINFO));
			purlmap->insert(URLMAP::value_type
				(url,info));
		}
	}
	
	pthread_mutex_unlock(&lock);
}

string Pool::GetUrl()
{
	pthread_mutex_lock(&lock);
	
	string url = urlqueue.front();
	urlqueue.pop();
	
	pthread_mutex_unlock(&lock);
	
	return url;
}

void Pool::AddTargetUrl(string url)
{
	pthread_mutex_lock(&lock);
	
	urlqueue.push(url);
	
	pthread_mutex_unlock(&lock);
}

void Pool::PrintPool()
{
	cout<<endl;
	for(HOSTMAP::iterator it = hostmap.begin();
		it != hostmap.end(); ++ it)
	{		
		cout<<it->first<<endl;
		URLMAP *purlmap = it->second;
		for(URLMAP::iterator itt = purlmap->begin();
			itt != purlmap->end(); ++itt)
		{
			cout<<it->first<<endl;
		}
		cout<<endl;
	}
}
