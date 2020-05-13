#include "bst.h"
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
BST<T>::BST() {
	//enpty tree
	root = NULL;
};

template<typename T>
BST<T>::~BST() {
	//we do this to leverage reccursion
	T* curr;
//	deleteTree(curr);
}

template<typename T>
void BST<T>::deleteTree(T* curr) {
	//referenced: https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
	//traversial var
	curr = root;

	if (curr == NULL) {

	}
	else {
		/*We go to the left all the way, then we go to it's right node.
		After we go up a generation and delete each node.*/
		deleteTree(curr->left);
		deleteTree(curr->right);

		//actual deletion of the node.
		delete curr;
	}


}

//will have to change for self balancing
template<typename T>
void BST<T>::printTree(T* node) {
	if (node == NULL) {
		return;
	}
	printTree(node->left);
	node->data->printDetails();
	printTree(node->right);
}

template<typename T>
void BST<T>::printTree() {
	if (isEmpty()) {
		return;
	}
	printTree(root);
}

template<typename T>
void BST<T>::outputTree(string fname) {
	if (isEmpty()) {
		return;
	}

	outputTree(root, fname);
}

template<typename T>
void BST<T>::outputTree(T* node, string fname) {
	if (node == NULL) {
		return;
	}
	outputTree(node->left, fname);

	string line = node->serialize();
	line = line + "\n"; // Need to add end of line
	ofstream file;
	file.open(fname, std::ios_base::app); // appends instead of overwrite
	file << line;
	file.close();

	outputTree(node->right, fname);
}

template<typename T>
T* BST<T>::getMax() {
	//go all the way to the right
	if (root == NULL) {
		return NULL;
	}
	T* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	return curr; // can return curr-> key
}

template<typename T>
T* BST<T>::getMin() {
	//go all the way to the left
	if (root == NULL) {
		return NULL;
	}
	T* curr = root;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	return curr; // can return curr-> key
}

template<typename T>
bool BST<T>::isEmpty() {
	if (root == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
void BST<T>::insert(T* node) {
	if (search(node->key)) {
		return;
	}

	//can't have duplicate keys so check for it
	if (isEmpty()) {
		//empty tree
		root = node;
		node->left = NULL;
		node->right = NULL;
		++size;
	}
	else {		
		//not an empty tree
		T* curr = root; //start at the root
		T* parent;

		while (true) {
			parent = curr;
			if (node->key < curr->key) {
				//go left				
				curr = curr->left;
				if (curr == NULL) {
					parent->left = node;
					node->left = NULL;
					node->right = NULL;
					++size;
					break;
				}
				
			}
			else {
				//go right
				curr = curr->right;
				if (curr == NULL) {
					parent->right = node;
					node->left = NULL;
					node->right = NULL;
					++size;
					break;
				}
			}

		}
	}
}

template<typename T>
bool BST<T>::search(int k) {

	if (isEmpty()) {
		return false;
	}
	else {
		//not an empty tree
		T* current = root;		
		while (current->key != k) {
			if (k < current->key) {
				current = current->left;
			}
			else {
				current = current->right;
			}
			//didn't find the value
			if (current == NULL) {
				return false;
			}
		}
	}

	return true;
}

template<typename T>
bool BST<T>::deleteNode(int k) {
	if (isEmpty())
		return false;
	T* parent = root;
	T* current = root;
	bool isLeft = true;

	while (current->key != k) {
		parent = current;
		if (k < current->key) {
			isLeft = true;
			current = current->left;
		}
		else {
			isLeft = false;
			current = current->right;
		}
		if (current == NULL)
			return false;
	}
	//if we make it here, we found the value, now we delete
	//check leaf node, children and L or R node
	// cout << "current key is " << current->key << " which matches " << k << endl;

	if (current->left == NULL && current->right == NULL) {
		//then have a leaf treenode
		//cout << "we have a leaf node" << endl;
		if (current == root) {
			root = NULL;
			--size;
			//cout << "current is root" << endl;
		}
		else if (isLeft) {
			parent->left = NULL;
			//cout << "current is left" << endl;
			free(current);
			--size;
		}
		else {
			parent->right = NULL;
			//cout << "current is right" << endl;
			free(current);
			--size;
		}
	}
	//here is whether on left or right, inside it is ab the children
	else if (current->right == NULL) { //no right child, so must have a left chile
		if (current == root) {
			root = current->left;
		}
		else if (isLeft)
			parent->left = current->left;
		else
			parent->right = current->left;
	}
	else if (current->left == NULL) { //no left child, so must have a right child
		if (current == root) {
			root = current->right;
		}
		else if (isLeft) {
			parent->left = current->right;
		}
		else {
			parent->right = current->right;
		}
	}
	else {
		//node to be deleted has two children

		T* successor = getSuccessor(current);
		if (current == root) {
			root = successor;
		}

		else if (isLeft) {
			parent->left = successor;
		}

		else {
			parent->right = successor;
		}


		//commect/link successor to current's (d) left child
		successor->left = current->left;

		return true;

	}
}


//****Assumes you already called search to see if the node exists****
template<typename T>
T* BST<T>::returnNode(int k) {
	T* current = root;
	while (current->key != k) {
		if (k < current->key)
			current = current->left;
		else
			current = current->right;
		//didn't find the value
		if (current == NULL) {
			cout << "Did not find the ID: " <<
				k << "." << endl;
			return NULL;
		}
	}
	return current;
}

template<typename T>
void BST<T>::reColor(T* node, bool c) {
	//Black -> Red
	if (c == true)
		c = false;

	//Red->Black
	else
		c = true;
}

template<typename T>
T* BST<T>::getSuccessor(T* d) {
	//the parameter d represents the node to be deleted
	T* current = d->right;
	T* sp = d;
	T* successor = d;

	while (current != NULL) {
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor != d->right) {
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

template<typename T>
T* BST<T>::getRoot() {
	return root;
}

template<typename T>
int  BST<T>::getSize() {
	return size;
}

//will have to change for self balancing
template<typename T>
void BST<T>::copyNode(T* newNode, T* node) {
	newNode->data = node->data;
	newNode->key = node->key;
	newNode->color = node->color;
	if (node->left) {
		T* newLeft = new T;
		newNode->left = newLeft;
		copyNode(newLeft, node->left);
	}
	if (node->right) {
		T* newRight = new T;
		newNode->right = newRight;
		copyNode(newRight, node->right);
	}
	this->insert(newNode);
}