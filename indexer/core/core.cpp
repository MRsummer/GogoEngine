/************************************************
*core logic of the indexer
*including : 
*	index files under a directory
*	update index
*	get result of query
*	start and stop index(sotre and restore)
*
*author : summer  2012/3/24
************************************************/

#include "core.h"

/*
*init all the core
*/
Core::Core()
{
	//create scws and index object
	pscws = new Scws();
	pindex = new Index();
	
	//restore index data
	Restore("index.data");
	
	//set changed false
	indexChanged = false;
}

/*
*destroy the core
*/
Core::~Core()
{
	//release the object
	delete pscws;
	delete pindex;
	
	//index changed
	if(indexChanged)
	{
		Store("index.data");
	}
}

/*
*index all the files under a directory (index a 
*package)
*/
void Core::IndexFiles(string path)
{
	vector<string> files;
	ListFiles(path,files);
	for(int id = 0;id < files.length();id ++)
	{
		Document doc = Document(files[id]);
		
		//parse title
		vector<SCWSRESULT> vtitle;
		pscws->GetResult(doc.GetTitle(),vtitle);
		
		//parse kwords
		vector<SCWSRESULT> vkwords;
		pscws->GetResult(doc.GetKwords(),vkwords);
		
		//parse description
		vector<SCWSRESULT> vdesc;
		pscws->GetResult(doc.GetDesc(),vdesc);		
		
		//parse content
		vector<SCWSRESULT> v;
		pscws->GetResult(doc.GetContent(),v);
			
		//concatenate the vectors
		v.insert(v.end(),vtitle.begin()
			,vtitle.end());
		v.insert(v.end(),vkwords.begin()
			,vkwords.end());
		v.insert(v.end(),vdesc.begin()
			,vdesc.end());
		
		//index all the word
		for(int i = 0;i < v.size();i ++)
		{
			string word = v[i].word;
			int docid = id;
			int score = vtitle[i].score;
			pindex->AddNode(word,docid,score
				,TITLEWEIGHT);
		}
	}//end of loop
}

/*
*get the result of multiple word query
*/
void Core::GetResult(vector<string> words,
	int limit,vector<DOCNODE> &ret)
{
	map<int,int> result;
	
	//get all the results and merge into the map
	for(int n = 0;n < words.size();n ++)
	{
		DOCLIST list = index.GetDocList(words[n]);
		for(int i = 0;i < list.size();i ++)
		{
			DOCNODE node = list[i];
			map<int,int>::iterator it = 
				result.find(node.docid); 
			if(it != result.end())
			{
				it->second += node.score;
			}
			else
			{
				result.insert(map<int,int>::value_ty\
					pe(node.docid,node.score));

			}
		}
	}
	
	//get the first 'limit' highest score
	//it is map isterator,itt is vector iterator
	//first push an element into vector ret
	map<int,int>::iterator it = result.begin();
	if(!result.empty())
	{
		DOCNODE node;
		node.docid = it->first;
		node.score = it->second;
		ret.push_back(node);
		++ it;
	}
	
	//first use insert sort, growing up in order
	for(int i = 0;it != result.end() && i < limit;
		++ it,++ i)
	{
		vector<DOCNODE>::iterator itt = ret.begin();
		for(;itt != ret.end();++ itt)
		{
			if(it->second > itt->score)
				continue;
			else
				break;
		}
		DOCNODE node;
		node.docid = it->first;
		node.score = it->second;
		ret.insert(itt - 1,node);
	}
	
	//compare and sort
	for(int i = limit;it != result.end() && 
		i < result.size();++ i,++ it)
	{
		vector<DOCNODE>::iterator itt = ret.begin();
		if(it->second > itt->score)
		{
			//get the insert pos
			for(;itt != ret.end();++ itt)
			{
				if(it->second > itt->score)
					continue;
				else
					break;
			}
			//insert the node to appropriate pos
			DOCNODE node;
			node.docid = it->first;
			node.score = it->second;
			ret.insert(itt - 1,node);
			//erase the first element
			ret.erase(ret.begin());
		}
	}

}
