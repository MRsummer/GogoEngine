/************************************************
*the search engine core structure
*author : summer  2012/3/24
************************************************/
#include "index.h"

/*
*add a word node to the doclist
*/
Index::AddNode(string word,int docid,int score
	,int weight)
{
	INDEX::iterator it = index.find(word);
	if(it == index.end())
	{
		DOCNODE node;
		node.docid = docid;
		node.score = score;
		DOCLIST list;
		list.push_back(node);
		index.insert(INDEX::value_type(word
			,list));
	}
	else
	{
		DOCLIST list = it->second;
		if(list.back().docid == docid)
		{
			list.back().score += score;
		}
		else
		{
			DOCNODE node;
			node.docid = docid;
			node.score = score;
			list.push_back(node);
		}
	}
}

/*
*get doclist by a word
*/
DOCLIST Index::GetDocList(string word)
{
	INDEX::iterator it = index.find(word);
	if(it != index.end())
	{
		return it->second;
	}
	return DOCLIST();
}

/*
*save index structure
*word-->doclist(docnode)
*/
void Index::Save(string filepath)
{
	File file = File(filepath,"a");
	for(INDEX::iterator it = index.begin();
		it != index.end(); ++it)
	{
		string content = "<item><word>";
		string word = it->first;
		content += word + "</word><list>";
		DOCLIST list = it->second;
		for(DOCLIST::iterator itt = list.begin();
			itt != list.end(); ++itt)
		{
			 content += itt->docid + "," 
					 + itt->socre + "&";
		}
		content += "</list></item>\n"
		file.WriteContent(content);
	}
	file.Close();
}

/*
*restore the index structure
*/
void Index::Restore(string filepath)
{
	File file = File(filepath,"r");
	string line;
	while((line = file.GetLine) != "")
	{
		int wordpos = line.find_first_of(
			"<word>") + 6;
		int wordlen = line.find_first_of(
			"</word>") - wordpos;
		string word = string(wordpos,wordlen);
		
		int listpos = line.find_first_of(
			"<list>") + 6;
		for(int n = listpos;n < line.length();
			n ++)
		{
			string sdocid;
			string sscore;
			int docid = 0;
			int score = 0;
			bool isDocid = true;
			
			if(line[n] == ',')
			{
				//get docid
				docid = stoi(sdocid);
				//change status
				isDocid = false;
				continue;
			}
			else if(line[n] == '&')
			{
				//get score
				score = stoi(sscore);
				//add new node to the index
				AddNode(word,docid,score,1);
				//judge exit condition
				if(line[n+1] == '<')
				{
					break;
				}
				//change status
				isDocid = true;
				continue;
			}
			else
			{
				if(isDocid)
				{
					sdocid += line[n];
				}
				else
				{
					sscore += line[n];
				}
			}
		}//end of readline
	}//end of read all lines
	
	//close the index file
	file.Close();
}