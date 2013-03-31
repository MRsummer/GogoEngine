/************************************************
*the search engine core structure
*author : summer  2012/3/24
************************************************/

#ifndef INDEX_H_
#define INDEX_H_

#include <map>
#include <string>

using namespace std;

//document node
typedef struct{
	int docid;
	int score;
}DOCNODE;
//document list
typedef list<DOCNODE> DOCLIST;
//index map
typedef map<string,DOCLIST> INDEX;

class Index
{
public:
	AddNode(string word,int docid,int score
		,int weight);
	GetDocList();
	void Save(string filepath);
	void Restore(string filepath);
private:
	INDEX index;
};

#endif /*INDEX_H_*/