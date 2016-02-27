#ifndef TREENODE_H_
#define	TREENODE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#define SAFE_DELETE(p) {if(p){delete p; p = 0;}}

using namespace std;
template <class T>
class TreeNode {
public:
	TreeNode();
	TreeNode(const T& _data);
	~TreeNode();

	
	const T& getData();
	size_t numOfChildren();
	TreeNode<T>* getChildAt(size_t _indx);
	TreeNode<T>* getParent();
	bool hasChild(TreeNode<T> *_node);

	void grafyNodes(TreeNode<T> *_nodes);
	void setParent(TreeNode<T> *_node);
	void setData(const T& _data);
	void addNode(TreeNode<T> *_node);
	void removeNodeByData(const T& _data);
	
private:
	T data;
	void removeChildren(TreeNode<T> *_node);
	TreeNode<T> *parent = NULL;
	vector<TreeNode<T>*> children;
	
};
template <class T>
TreeNode<T>::TreeNode() {
	
}

template <class T>
TreeNode<T>::TreeNode(const T& _data) {
	data = _data;
}

template <class T>
TreeNode<T>::~TreeNode() {
}

template <class T>
void TreeNode<T>::addNode(TreeNode<T> *_node) {
	children.push_back(_node);
}

template <class T>
void TreeNode<T>::removeNodeByData(const T& _data)
{
	for (size_t i = 0; i < numOfChildren(); i++)
	{
		if (children[i]->getData() == _data)
		{
			removeChildren(children[i]);
			children.erase(children.begin() + i);
		}
		else
		{
			cout << "No such child node!" << endl;
		}
	}

	
}

template <class T>
void TreeNode<T>::removeChildren(TreeNode<T> *_node)
{
	for (size_t i = 0; i < _node->numOfChildren(); i++)
	{
		removeChildren(_node->getChildAt(i));
	}
	
	SAFE_DELETE(_node);
}
template <class T>
const T& TreeNode<T>::getData() {
	return data;
}

template <class T>
void TreeNode<T>::setData(const T& _data) {
	data = _data
}

template <class T>
size_t TreeNode<T>::numOfChildren() {
	return children.size();
}

template <class T>
TreeNode<T>* TreeNode<T>::getChildAt(size_t _indx)
{
	return children[_indx];
}

template <class T>
TreeNode<T>* TreeNode<T>::getParent()
{
	return parent;
}

template <class T>
bool TreeNode<T>::hasChild(TreeNode<T> *_node)
{
	for (size_t i = 0; i < numOfChildren(); i++)
	{
		if (children[i]->getData() == _node->getData())
		{
			return true;
		}
		
	}
	return false;
}

template <class T>
void TreeNode<T>::setParent(TreeNode<T> *_node)
{
	parent = _node;
}


template <class T>
void TreeNode<T>::grafyNodes(TreeNode<T> *_node)
{
	for (size_t i = 0; i < _node->numOfChildren(); i++)
	{
		_node->children[i]->setParent(this);
		children.push_back(_node->children[i]);
	}
	
}

#endif

