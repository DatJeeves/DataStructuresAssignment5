#include "treeNode.h"
#include <iostream>
#include <cstddef>

// Contains the generic implementation of a treeNode for a BST.
// Note the node contains color to allow it to be used for a self-balancing tree
using namespace std;

//treenode implementation
template<typename T>
TreeNode<T>::TreeNode() {
	key = 0;
	data;
	color = false;
	left = NULL;
	right = NULL;
}

template<typename T>
TreeNode<T>::TreeNode(int k, T* record) {
	key = k;
	data = record;
	color = false;
	left = NULL;
	right = NULL;
}


template<typename T>
void TreeNode<T>::print() {
	// Assumes data has a print method
	data.printDetails();
}

template<typename T>
string TreeNode<T>::serialize() {
	// Assumes data has a print method
	return data->getCSV();
}

template<typename T>
TreeNode<T>::~TreeNode() {
	//have delete for diff types
	//in this test we delete student
	delete data;
}


