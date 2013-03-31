#include "dir.h"

void ListFiles(string path,vector<string> &files)
{
	DIR *dp;
	struct dirent *ep; 
	int dirNum = 0;
	bool exitDir = true;
	
	//check if the path include "/"
	if(path[path.length()] != "/")
	{
		path += "/";
	}
	
	//open directory
	dp = opendir (path.c_str());
	if(dp == NULL)
	{
		PrintErrorAndExit("path is not valid");
	}
	
	//read directory files
	while (ep = readdir(dp))
	{
		string filename = string(ep->d_name);
		
		if(exitDir && (filename == "." 
			|| filename == ".."))
		{
			dirNum ++;
			if(dirNum == 2)
			{
				exitDir = false;
			}
		}
		else
		{
			files.push_back(path + filename);
		}
	}
}