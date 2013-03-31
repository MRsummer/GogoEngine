#include "str.h"

void ReplaceChar(string &str,char oldv,char newv)
{
	for(string::size_type i = 0;i < str.size();
		i ++)
	{
		if(str[i] == oldv)
			str[i] = newv;
	}
}
