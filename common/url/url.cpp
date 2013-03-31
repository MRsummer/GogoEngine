#include "url.h"

string ProcessUrl(string urlstr,string host)
{
	if(urlstr.substr(0,7) == "http://")
	{
		return string(urlstr,7);
	}
	else if(urlstr[0] == '/')
	{
		return host + urlstr;
	}
	else
	{
		//drop https url,drop javascript action,
		//drop relative url
		return "";
	}
}

string GetHostByUrl(string url)
{
	size_t pos = url.find_first_of("/");
	return pos > 0 ? string(url,0,pos) : url;
}

string GetResourceByUrl(string url)
{
	size_t pos = url.find_first_of("/");
	return pos > 0 ? string(url,pos) : "/";
}
