#include <iostream>
#include "Tree.h"
#include "TreeNode.h"
#include "FileParse.h"
#include <string>
using namespace std;
#define LOG(x) {cout << x << endl;}
void getInputOptions(string _input);
string input;
string chooseOutput;
FileParse *fp = new FileParse();
int main(int argc, char* argv[])
{ 
	chooseOutput = "Please choose the number option to run a command: ";
	cout << chooseOutput << endl;
	cout << "(0) Load file." << endl;
	cout << "(1) Add Node to a parent node." << endl;
	cout << "(2) Remove Node from a parent node, include the child nodes." << endl;
	cout << "(3) Display Structure." << endl;
	cout << "(4) Quit." << endl;
	cout << endl;
	cout << "#>";
	cin >> input;

	getInputOptions(input);
	
	
	return 0;
} 

void getInputOptions(string _input)
{
	if (_input == "0")
	{
		
		string fileName;
		cout << "Please type the file name: " << endl;
		cout << "#>";
		cin >> fileName;
		if (fp->loadFile(fileName))
			cout << chooseOutput << endl;
		cout << endl;
		cout << "#>";
		cin >> input;
		getInputOptions(input);
	}
	else if (_input == "1")
	{
		string pNode;
		string cNode;
		cout << "Please type the parent node you want to add child into:" << endl;
		cout << "#>";
		cin >> pNode;
		cout << "Please type the child node you want to add:" << endl;
		cout << "#>";
		cin >> cNode;
		if (fp->addNode(pNode, cNode))
			cout << chooseOutput << endl;
		else
			cout << "Please type the node again!" << endl;
		cout << endl;
		cout << "#>";
		cin >> input;
		getInputOptions(input);
	}
	else if (_input == "2")
	{
		string pNode;
		string cNode;
		cout << "Please type the parent node you want to delete child from:" << endl;
		cout << "#>";
		cin >> pNode;
		cout << "Please type the child node you want to delete:" << endl;
		cout << "#>";
		cin >> cNode;
		
		fp->removeNode(pNode, cNode);

		cout << chooseOutput << endl;
		cout << endl;
		cout << "#>";
		cin >> input;
		getInputOptions(input);
	}
	else if (_input == "3")
	{
		if (fp->printOut())
			cout << chooseOutput << endl;
		cout << endl;
		cout << "#>";
		cin >> input;
		getInputOptions(input);
	}
	else if (_input == "4")
	{
		return;
	}
	else if (_input == "q")
	{
		return;
	}
	else
	{
		cout << "Incorrect command given. Please try again" << endl;
		cout << "#>";
		cin >> input;
		getInputOptions(input);
	}
}