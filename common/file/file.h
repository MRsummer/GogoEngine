/*********************************************
*basic file read and write operations
*author:summer 2013/3/22
*********************************************/
#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define BUFFERSIZE 1024

class File
{
public:
	//open the file
	File(string filepath,string mode);
	
	//if the file is not closed,close it
	~File();
	
	//get the file content to string
	string ReadContent();
	
	//write the content to the file,depending
	//on the mode
	void WriteContent(string content);
	
	//close the file and release the memory
	void Close();
	
	//get line from file
	string GetLine();
	
	//get each line of the file and put it into
	//a vector	
	void GetLines(vector<string> &v);
	
	//write lines to file
	void WriteLines(vector<string> v);
	
	//get lines from file
	void GetLines(vector<string> &v
		,int linenum);
private:
	FILE *fp;
	bool closed;
};

#endif /*FILE_H_*/
