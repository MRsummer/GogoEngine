/*********************************************
*basic file read and write operations
*author:summer 2013/3/22
*********************************************/
#include "file.h"

File::File(string filepath,string mode)
{
	fp = fopen(filepath.c_str(),mode.c_str());
	closed = false;
}

File::~File()
{
	if(!closed)
	{
		fclose(fp);
	}
}

void File::Close()
{
	fclose(fp);
}

string File::ReadContent()
{
	string content = "";
	char buf[BUFFERSIZE] = {0};
	while(fread(buf,BUFFERSIZE,1,fp) > 0)
	{
		content += buf;
		memset(buf,0,BUFFERSIZE);
	}
	return content;
}

void File::WriteContent(string content)
{
	fwrite(content.c_str(),content.length()+1,1
		,fp);
}

void File::GetLines(vector<string> &v)
{
	char *line = NULL;
	while(getline(&line,0,fp) > 0)
	{
		v.push_back(string(line));
	}
	if(line)
		free(line);
}

void File::WriteLines(vector<string> v)
{
	string content;
	for(int i = 0;i < v.size();i ++)
	{
		content += v[i] + "\n";
	}
	WriteContent(content);
}

string File::GetLine()
{
	char *line = NULL;
	string res = "";
	if(getline(&line,0,fp) > 0)
	{
		res = line;
	}
	if(line)
		free(line);
	return res;
}

void File::GetLines(vector<string> &v,int linenum)
{
	int i = 0;
	char *line = NULL;
	while(getline(&line,0,fp) > 0 && i < linenum)
	{
		v.push_back(string(line,0,strlen(line)-1));
		i ++;
	}
	if(line)
		free(line);
}
