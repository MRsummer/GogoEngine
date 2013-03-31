#include "document.h"

Regx Document::titleRegx = 
	Regx("<title>([^<]*)</tiltle>");
	
Regx Document::descRegx = 
	Regx("<meta[^>]*name=[\'\"]description[\'\"]"
	"[^>]*content=[\'\"]([^>]*)[\'\"][^>]*>");
	
Regx Document::kwordsRegx = 
	Regx("<meta[^>]*name=[\'\"]keywords[\'\"]"
	"[^>]*content=[\'\"]([^>]*)[\'\"][^>]*>");
	
Regx Document::bodyRegx = 
	Regx("<body>([^<]*)</body>");

Document::Document(string filepath
	,string savedocpath)
{
	//read the content
	File file = File(filepath,"r");
	string content = file.ReadContent();
	
	//get file parts
	title = titleRegx.Match(content,1);
	title = RemoveBreakLines(title);
	
	desc = descRegx.Match(content,1);
	desc = RemoveBreakLines(desc);
	
	kwords = kwordsRegx.Match(content,1);
	kwords = RemoveBreakLines(kwords);
	
	content = bodyRegx.Match(content,1);
	content = RemoveTags(content);
	
	//save the document
	File file = File(savedocpath,"w");
	vector<string> v;
	v.push("<document>");
	v.push(title);
	v.push(kwords);
	v.push(desc);
	v.push(content);
	v.push("</documnet>");
	file.WriteLines(v);
	file.Close();
}

Document::Document(string docpath)
{
	File file = File();
	vector<string> v;
	file.GetLines(v,6);
	if(v[0] != "<document>" 
		|| v[6] != "</document>")
	{
		PrintAndExit("document file error");
	}
	title = v[1];
	kwords = v[2];
	desc = v[3];
	content = v[4];
	file.Close();
}

string Document::RemoveTags(string content)
{
	bool isContent = true;
	string ret = "";
	for(int i = 0;i < content.length();i ++)
	{
		if(content[i] == '<')
		{
			isContent = false;
			continue;
		}
		else if(i >= 1 && content[i-1] == '>')
		{
			isContent = true;
			ret += " ";
		}
		
		//remove tags and break lines
		if(isContent && content[i] != '\n' 
			&& content[i] != '\r')
		{
			ret += content[i];
		}
	}
	return ret;
}

string Document::RemoveBreakLines(stirng content)
{
	string ret;
	for(int i = 0;i < content.length();i ++)
	{
		if(content[i] != '\r' 
			&& content[i] != '\n')
		{
			ret += content[i];
		}
	}
	return ret;
}