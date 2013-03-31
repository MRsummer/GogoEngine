#include "regx.h"

Regx::Regx(string pattern)
{
	if(regcomp(&preg,pattern.c_str(),REG_EXTENDED) 
		!= 0)
	{
		PrintErrorAndExit("regcomp");
	}
}

string Regx::MatchOnce(string content
	,int patternIndex)
{
	regmatch_t pmatch[10];
	string ret = "";
	if(regexec(&preg,content.c_str(),10,pmatch
		,REG_NOTBOL) != REG_NOMATCH)
	{
		int len = pmatch[patternIndex].rm_eo 
			- pmatch[patternIndex].rm_so;
		ret = string(content
			,pmatch[patternIndex].rm_so,len);		
	}
	return ret;
}

int Regx::Match(string content,vector<string> &v
	,int patternIndex)
{
	regmatch_t pmatch[10];	
	char *pos = (char *)content.c_str();
	int matched = -1;
	
	//match in a loop
	while(regexec(&preg,pos,10,pmatch,REG_NOTBOL)
		!= REG_NOMATCH)
	{
		//calculate the len and get the string
		int len = pmatch[patternIndex].rm_eo 
			- pmatch[patternIndex].rm_so;
		string match = string(content
			,pmatch[patternIndex].rm_so,len);
		
		//push the result to the vector
		v.push_back(match);		
		
		//add the offset
		pos += pmatch[patternIndex].rm_so + len;
		
		//modify the flag
		matched = 0;
	}
	
	return matched;
}

Regx::~Regx()
{
	regfree(&preg);
}
