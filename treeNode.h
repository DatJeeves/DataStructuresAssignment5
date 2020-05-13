#ifndef TREENODE_H
#define TREENODE_H
#include "student.h"
#include "list.h"

using namespace std;
template<typename T>
class TreeNode {
public:
	//vars for node data and to search on
	int key;
	T* data;

	//Constructors & Destructor 
	TreeNode();
	/*has a key-value pair so can search on id number
	and have it's particular data*/
	//TreeNode(int k, int value);
	TreeNode(int k, T* record);
	void print();
	string serialize();
	~TreeNode();
	//have virtual destructor for student/faculty


		// Overloading operators
//  - https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
//  - https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm

	bool operator < (T* n2) { (key < n2.key) ? true : false; }
	bool operator > (T* n2) { (key > n2.key) ? true : false; }
	bool operator == (T* n2) { (key == n2.key) ? true : false; }
	bool operator != (T* n2) { (key != n2.key) ? true : false; }
	bool operator >= (T* n2) { (key >= n2.key) ? true : false; }
	bool operator <= (T* n2) { (key <= n2.key) ? true : false; }

	/* 
	******SUPER IMPORTANT**********
		FALSE = RED
		TRUE = BLACK
	*/
	bool color;
	TreeNode* left;
	TreeNode* right;
};

#endif