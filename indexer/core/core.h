/************************************************
*core logic of the indexer
*author : summer  2012/3/24
************************************************/
#ifndef INDEX_CORE_H_
#define INDEX_CORE_H_

#include <string>
#include <vector>

#include "../../common/dir/dir.h"
#include "../scws/scws.h"
#include "../document/document.h"
#include "../index/index.h"

using namespace std;

//weight macros
#define TITLEWEIGHT 5
#define KWORDSWEIGHT 5
#define DESCWEIGHT 3
#define CONTENTWEIGHT 1

class Core
{
public:
	Core();
	~Core();
	//index files under a directory
	void IndexFiles(string path);
	//get the result of query
	void GetResult(vector<string> words);
private:
	Scws *pscws;
	Index *pindex;
	bool indexChanged;
};

#endif /*INDEX_CORE_H*/