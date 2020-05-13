#ifndef BST_H
#define BST_H
#include "treeNode.h"

using namespace std;
template<typename T>
class BST {
public:
	//Constructor
	BST();
	//assumes template class has a virtual destructor
	~BST();

	//methods to augment the tree
	void insert(T* node);
	T*  getRoot();
	bool search(int k);
	bool deleteNode(int key);
	void deleteTree(T* curr);
	T* returnNode(int key);
	void outputTree(string fname);
	void outputTree(T* node, string fname);

	//red-black method
	void reColor(T* node, bool color);

	//methods to check the tree metrics
	T* getMin();
	T* getMax();
	bool isEmpty();
	int getSize();

	//extra help methods
	T* getSuccessor(T* next);
	void printTree(T* node);
	void printTree();
	void copyNode(T* newNode, T* fromNode);

private:
	T* root;
	int size = 0;

};

#endif