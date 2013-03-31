#include "error.h"

void Print(string msg)
{
	cout<<msg<<endl;
}

void PrintAndExit(string msg)
{
	Print(msg);
	exit(1);
}

void PrintError(string msg)
{
	cout<<msg<<":"<<string(strerror(errno))<<endl;
}

void PrintErrorAndExit(string msg)
{
	PrintError(msg);
	exit(1);
}

void LogError(string msg)
{
	File file = File(ERRORFILE,"a");
	file.WriteContent(msg);
	file.Close();
}

void LogErrorAndExit(string msg)
{
	LogError(msg);
	exit(1);
}
