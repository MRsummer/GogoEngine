/************************************************
*function : parse a document , save a document 
*or read a document by documentid. it has specific
*files to record the documentid
*author : summer  2013/3/24
************************************************/

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include "../../common/file/file.h"

#include <string>
#include <vector>

using namespace std;

class Document
{
public:
	Document(string filepath);
	Document(int docid);
	string GetTitle(){ return title;}
	string GetKwords(){ return kwords;}
	string GetDesc(){ return desc;}
	string GetContent(){ return content;}
	static Regx titleRegx;
	static Regx kwordsRegx;
	static Regx descRegx;
	static Regx bodyRegx;
private:
	string title;
	string kwords;
	string desc;
	string content;
	string RemoveTags(string content);
	string Document::RemoveBreakLines
		(stirng content);
};

#endif /*DOCUMENT_H_*/