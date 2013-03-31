#include "scws.h"

Scws::Scws()
{
	if (!(s = scws_new()))
	{
		PrintErrorAndExit("scws_new");
	}
	
	//set basic settings
	scws_set_charset(s, "utf8");
	scws_set_dict(s, "/usr/local/scws/etc/"
		"dict.utf8.xdb",SCWS_XDICT_XDB);
	scws_set_rule(s, "/usr/local/scws/etc/"
		"rules.utf8.ini");
}

void Scws::GetResult(string content
	,vector<SCWSRESULT> &v)
{  
	scws_res_t res, cur;
	scws_send_text(s,content.c_str()
		,content.length());
	
	while (res = cur = scws_get_result(s))
	{
		while (cur != NULL)
		{
			//add the result into the vector
			SCWSRESULT result;
			result.word = string(content,cur->off
				,cur->len);
			result.weight = (int)cur->idf;
			v.push(result);
			
			//offset the cur
			cur = cur->next;
		}
		scws_free_result(res);
	}
	scws_free(s);
}