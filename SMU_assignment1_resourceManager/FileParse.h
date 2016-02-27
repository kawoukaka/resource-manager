#ifndef FILEPARSE_H_
#define	FILEPARSE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <map>
#include "Tree.h"
#define LOG(x) {cout << x << endl;}

using namespace std;
class FileParse
{
public:
	FileParse();
	~FileParse();
	bool loadFile(string _fileName);
	bool addNode(string _pData, string _cData);
	bool removeNode(string _pData, string _cData);
	bool printOut();
	vector<TreeNode<string>*> getTotalNodes();
private:
	vector<string> split(string str, string pattern); 
	vector<TreeNode<string>*> totalNodes; //store total nodes in the file
	vector<TreeNode<string>*> treeRoots;  //store total tree roots (which are not associated with other tree nodes)
	vector<string> vString; //store the split value in every line
	vector<string> headData;  //all the front split value in every line
	void producingRelationship(multimap<string,string> _map);
};

FileParse::FileParse()
{

}

FileParse::~FileParse()
{
	vector<TreeNode<string>*>().swap(totalNodes);
	vector<TreeNode<string>*>().swap(treeRoots);
	vector<string>().swap(vString);
}


vector<TreeNode<string>*> FileParse::getTotalNodes()
{
	return totalNodes;
}
bool FileParse::addNode(string _pData, string _cData)
{
	TreeNode<string> *newNode = new TreeNode<string>(_cData);
	if (find(headData.begin(), headData.end(), _pData) != headData.end()!=true)
	{
		cout << "No such parent Node!" << endl;
		return false;
	}
	for (size_t indx = 0; indx < totalNodes.size(); indx++)
	{
		
		if (totalNodes[indx]->getData() == _pData)
		{
			totalNodes[indx]->addNode(newNode);
			newNode->setParent(totalNodes[indx]);
			totalNodes.push_back(newNode);
			return true;
		}
		
	}
	
	

}
bool FileParse::removeNode(string _pData, string _cData)
{
	if(find(headData.begin(), headData.end(), _pData) != headData.end() != true)
	{
		cout << "No such parent Node!" << endl;
		return false;
	}

	for (size_t indx = 0; indx < totalNodes.size(); indx++)
	{
		
		if (totalNodes[indx]->getData() == _pData)
		{
			totalNodes[indx]->removeNodeByData(_cData);
			return true;
		}
		
	}

	//printOut();
}
bool FileParse::loadFile(string _fileName)
{
	totalNodes.clear();
	treeRoots.clear();
	vString.clear();

	try {
		ifstream file(_fileName);

		string line;

		multimap<string, string> relationMap;

		while (getline(file, line)) {

			vString = split(line, " ");
			relationMap.insert(pair<string, string>(vString.front(), vString.back()));

		}
		producingRelationship(relationMap);
		printOut();
	}
	catch (ios_base::failure& e) {
		cerr << e.what() << '\n';
	}
	return true;
}

/*
Map:
key:bomb value:iron
key:bomb value:chip
key:ore value:bomb 

1. If the map has duplicate key, remove duplicate one and link unique key with single/multiple value; 

key:bomb value:ore
key:bomb value:chip

2. If the map has one key same as the other value is not pair with this key, link 
key:bomb value:chip
key:rocket value:bomb

*/
void FileParse::producingRelationship(multimap<string, string> _map)
{
	TreeNode<string> *pNode;  //store the nodes with split value (front) 
	TreeNode<string> *cNode;  //store the nodes with split value (back)
	vector<string> valueData;  //store the back split value

	vector<TreeNode<string>*> headNodes;  //store the nodees with split value array (front) 
	vector<TreeNode<string>*> valueNodes;  //store the nodes with split value array (back)

	//get all key from map
	for (multimap<string, string>::iterator multimapIt = _map.begin(); multimapIt != _map.end(); ++multimapIt) 
	{
		headData.push_back(multimapIt->first);
		valueData.push_back(multimapIt->second);
	}

	//remove duplicate key. Ex: bomb ore, bomb chip.
	sort(headData.begin(), headData.end());
	headData.erase(unique(headData.begin(), headData.end()), headData.end());

	//link key with multiple value
	for (size_t i = 0; i < headData.size(); i++)
	{
		pair<multimap<string, string>::iterator, multimap<string, string>::iterator> pMap;
		pNode = new TreeNode<string>(headData[i]);
		headNodes.push_back(pNode);
		
		pMap = _map.equal_range(headData[i]);

		for (multimap<string, string>::iterator it2 = pMap.first; it2 != pMap.second;++it2)
		{
			
			cNode = new TreeNode<string>(it2->second);
			pNode->addNode(cNode);
			cNode->setParent(pNode);
			valueNodes.push_back(cNode);
			
		}
	}

	
	totalNodes.insert(totalNodes.end(), headNodes.begin(), headNodes.end());
	totalNodes.insert(totalNodes.end(), valueNodes.begin(), valueNodes.end());

}

bool FileParse::printOut()
{
	treeRoots.clear();
	for (size_t indx = 0; indx < totalNodes.size(); indx++)
	{
		if (totalNodes[indx]->getParent() == NULL)
		{
			treeRoots.push_back(totalNodes[indx]);
		}
	}

	for (size_t indx = 0; indx < treeRoots.size(); indx++)
	{
		Tree<string> *t = new Tree<string>();
		t->setRoot(treeRoots[indx]);
		t->displayTree(t->root, 0);
		delete t;
	}
	return true;
}
vector<string> FileParse::split(string str, string pattern)
{
	int pos;
	vector<string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	
	return result;
}

#endif