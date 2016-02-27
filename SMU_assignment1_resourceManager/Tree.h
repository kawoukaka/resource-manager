#ifndef TREE_H_
#define	TREE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include "TreeNode.h"

#define SAFE_DELETE(p) {if(p){delete p; p = 0;}}
using namespace std;

template <class T>
class Tree {
public:
	Tree();
	~Tree();
	void displayTree(TreeNode<T> *_currentNode, size_t depth);
	void displayLevels();
	void displayFullTree();
	void setRoot(TreeNode<T> *_node);
	TreeNode<T> *root;
private:
	stack<TreeNode<T>*> s;
};

template <class T>
Tree<T>::Tree() {

}

template <class T>
Tree<T>::~Tree() {

}

template <class T>
void Tree<T>::setRoot(TreeNode<T> *_node) {
	root = _node;
}
template <class T>
void Tree<T>::displayTree(TreeNode<T> *_currentNode,size_t depth) {

	for (size_t i = 0; i < depth; i++)
		std::cout << " ";

	std::cout << "-";
	std::cout << _currentNode->getData() << std::endl;

	for (size_t i = 0; i < _currentNode->numOfChildren(); i++)
		displayTree(_currentNode->getChildAt(i), depth + 1);
}

template <class T>
void Tree<T>::displayFullTree()
{
	
}


template <class T>
void Tree<T>::displayLevels() {
	cout << endl << "Levels Display:" << endl;
	if (root == NULL) return;
	queue<TreeNode<T>*> curLevel;
	queue<int> level;
	curLevel.push(root);
	size_t plev = 0;
	level.push(plev);
	while (!curLevel.empty()) {
		//check the level first,if moved to next level, print a enter
		
		size_t clev = level.front();
		level.pop();
		
		if (plev<=clev) {
			plev = clev;
		}
		//pop the node
		TreeNode<T> *p = curLevel.front();
		cout << p->getData() << " " << endl;
		curLevel.pop();
		//push its children
		size_t i = 0;
		while (i < p->numOfChildren()) {
			curLevel.push(p->getChildAt(i));
			level.push(clev + 1); //update children's level
			i++;
		}
	
	}
	

}


#endif

