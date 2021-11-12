/*****************************************
* Shahrood User ID:  -
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef ABSTRACT_TREE_H
#define ABSTRACT_TREE_H

#include <iostream>
#include "exception.h"
#include "stack.h"
using namespace std;

class AbstractTree {
public:
	class TreeNode {
	public:
		TreeNode(int const&, TreeNode* = nullptr);

		int value() const;
		int degree() const;
		TreeNode* getParent() const;
		//TreeNode* child(int const&) const;

	private:
		int nodeValue;
		TreeNode* parent;
		DoubleLinkedList<TreeNode*>* children = new DoubleLinkedList<TreeNode*>;

		friend AbstractTree;
	};

	AbstractTree(int const&);
	AbstractTree(AbstractTree const&);
	~AbstractTree();

	// Accessors
	int size() const;
	int height() const;
	bool empty() const;

	bool find(int const&);
	int count(int const&);
	int getMaxDegree();

	// Mutators
	void push(int const&);
	void push(int*&, int const&);
	int pop();

	// Printers
	void printBFS(std::ostream&);
	void printDFS(std::ostream&);

private:
	TreeNode* root = nullptr;
	int maxDegree = 0;
	int treeSize = 0;
	DoubleLinkedList<TreeNode*> insertion;
	int counterIterator = 0;

	// Enter your implementation here
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

AbstractTree::AbstractTree(int const& maxDeg) : maxDegree(maxDeg)

{
	// Enter your implementation here	
}

AbstractTree::AbstractTree(AbstractTree const& tree)
{
	maxDegree = tree.maxDegree;
	if (!tree.empty()) {
		DoubleLinkedList<TreeNode*> bfs;
		TreeNode* current = tree.root;
		bfs.pushBack(current);
		while (!bfs.empty()) {
			current = bfs.front();
			push(current->nodeValue);
			bfs.popFront();
			for (int i = 0; i < current->children->size(); i++)
			{
				bfs.pushBack(current->children->getValueAt(i));
			}

		}
	}

	
}

AbstractTree::~AbstractTree() {
	// Enter your implementation here
}

// Enter your implementation here

AbstractTree::TreeNode::TreeNode(
	int const& nv,
	TreeNode* parent) : nodeValue(nv) , parent(parent)
	// Updated the initialization list here
{

}

int AbstractTree::TreeNode::value() const {
	return nodeValue;
}


int AbstractTree::TreeNode::degree() const
{
	
	return children->size();
}

AbstractTree::TreeNode* AbstractTree::TreeNode::getParent() const
{
	return parent;
}
int AbstractTree::size() const
{
	return treeSize;
}
int AbstractTree::height() const
{
	if (root == nullptr) return -1;
	int height = 0;
	TreeNode* temp = root;
	while (temp != nullptr && temp->children->size() != 0) {
		temp = temp->children->front();
		height++;
	}
	return height;
}
bool AbstractTree::empty() const
{
	return root == nullptr;
}
bool AbstractTree::find(int const& val)
{
	Stack<TreeNode*> dfs;
	TreeNode* currentNode = root;
	dfs.push(root);
	while (!dfs.isEmpty()) {
		if (currentNode->value() == val) return true;
		dfs.pop();
		for (int i = 0; i < currentNode->children->size(); i++)
		{
			dfs.push(currentNode->children->getValueAt(i));
		}
		if (!dfs.isEmpty())currentNode = dfs.top();
		else return false;
	}
	return false;
}
int AbstractTree::count(int const& val)
{
	Stack<TreeNode*> dfs;
	int counter = 0;
	TreeNode* currentNode = root;
	dfs.push(root);
	while (!dfs.isEmpty()) {
		if (currentNode->value() == val) counter++;
		dfs.pop();
		for (int i = 0; i < currentNode->children->size(); i++)
		{
			dfs.push(currentNode->children->getValueAt(i));
		}
		if (!dfs.isEmpty())currentNode = dfs.top();
		else return counter;
	}
	return counter;

}
int AbstractTree::getMaxDegree()
{
	return maxDegree;
}
void AbstractTree::push(int const& val)
{
	
	if (root == nullptr) { 
		root = new TreeNode(val); 
		insertion.pushFront(root);
	}
	else {

		if (insertion.front()->children->size() >= maxDegree) insertion.popFront();
		TreeNode* temp = new TreeNode(val, insertion.front());
		insertion.pushBack(temp);
		insertion.front()->children->pushBack(temp);
	
	}
	treeSize++;
}
void AbstractTree::push(int*& dataArray, int const& length)
{
	for (int i = 0; i < length; i++)
	{
		push(dataArray[i]);
	}

}

int AbstractTree::pop()
{
	DoubleLinkedList<TreeNode*> Queue;
	if (root != nullptr) {
		if (treeSize == 1) {
			int val = root->nodeValue;
			delete root;
			root = nullptr;
			treeSize--;
			return val;

		}
		Queue.pushBack(root);
		TreeNode* targetNode = root;
		while (!Queue.empty()) {
			for (int i = 0; i < targetNode->children->size(); i++)
			{
				Queue.pushBack(targetNode->children->getValueAt(i));
			}
			Queue.popFront();
			if(!Queue.empty())targetNode = Queue.front();
			
		}
		int val = targetNode->value();
		targetNode->parent->children->erase(targetNode);
		delete targetNode;
		treeSize--;
		return val;
		

	}
	else throw Underflow();

	return 0;
}
void AbstractTree::printBFS(std::ostream& out)
{
	out << "START->";
	if (!empty()) {
		DoubleLinkedList<TreeNode*> bfs;
		TreeNode* current = root;
		bfs.pushBack(current);
		while (!bfs.empty()) {
			current = bfs.front();
			out << current->nodeValue << "->";
			bfs.popFront();
			for (int i = 0; i < current->children->size(); i++)
			{
				bfs.pushBack(current->children->getValueAt(i));
			}

		}
	}

	out << "END" << endl;
}
void AbstractTree::printDFS(std::ostream& out)
{
	out << "START->";
	if (!empty()) {
		Stack<TreeNode*> dfs;
		TreeNode* current = root;
		dfs.push(current);
		while (!dfs.isEmpty()) {
			current = dfs.top();
			out << current->nodeValue << "->";
			dfs.pop();
			for (int i = current->children->size() - 1; i >=0 ; i--)
			{
				dfs.push(current->children->getValueAt(i));
			}

		}
	}

	out << "END" << endl;
}
// Enter your implementation here

#endif