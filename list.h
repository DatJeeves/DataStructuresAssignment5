#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <exception>
#include <iostream>


using namespace std;

/* A double linked list to store Generic nodes*/
template<typename T>
class List {
public:
	//pointers for the doubly linked list
	Node<T>* head; // Head of the list
	Node<T>* tail; // End of the list

	List();
	T GetHead();
	T GetTail();
	void AddToTail(T data);
	void AddToHead(T data);
	bool isEmpty();
	T popHead();
	T popTail();
	bool search(T data);
	void remove(T data);
	int GetListSize();

	~List();

private:
	//var for size of linked list
	int size;
};

template <typename T>
List<T>::List() {
	// Create an empty list
	head = NULL;
	tail = NULL;
	size = 0;
}

//Checks whether the List is empty via the size variable
template <typename T>
bool List<T>::isEmpty() {
	if (size == 0)
		return true;
	else
		return false;
}

template<typename T>
T List<T>::GetHead()
{
	return head->data;
}

template<typename T>
T List<T>::GetTail()
{
	return tail->data;
}


/*Inserts a value at the head of the list.
NOTE this means:
If the list is empty, then the inserted node becomes the
head AND tail node.

If the list isn't empty, then we have to update
the head node as well as it's next value. Then we have to
update the previous head node's prev value. Note that we
don't have to set the previous head node's prev pointer
to NULL because as being the previous head node, it's prev
pointer already pointed to NULL.

Lastly, we finish the method off the method by
incrementing it's size.
*/
template<typename T>
void List<T>::AddToHead(T data)
{
	Node<T>* n = new Node<T>();
	n->data = data;
	n->prevNode = NULL;
	n->nextNode = NULL;

	if (isEmpty()) {
		head = n;
		tail = head;
	}
	else {
		n->nextNode = head;
		head->prevNode = n;
		head = n;
	}
	++size;
}

template<typename T>
void List<T>::AddToTail(T data)
{
	Node<T>* n = new Node<T>();
	n->data = data;
	n->prevNode = NULL;
	n->nextNode = NULL;

	if (isEmpty()) {
		// Tail and head will do the same thing
		head = n;
		tail = head;
	}
	else {
		n->prevNode = tail;
		tail->nextNode = n;
		tail = n;
	}
	++size;

}

template <typename T>
T List<T>::popHead() {
	T answer;

	if (isEmpty()) {
		throw "ERROR: Trying to pop from an empty stack";
	}

	// added both checks for NULL and isEmpty for safety
	if ((head != NULL) || isEmpty()) {
		answer = head->data;
		head = head->nextNode;
		if (head != NULL) {
			head->prevNode = NULL;
		}
		--size;
		return answer;
	}
	else {
		throw "ERROR: Trying to pop from an empty stack";
	}
}

template <typename T>
T List<T>::popTail() {

	T answer;

	if (isEmpty()) {
		throw "ERROR: Trying to pop from an empty stack";
	}
	answer = tail->data;
	tail = tail->prevNode;
	tail->nextNode = NULL;
	--size;
	return answer;
}

template <typename T>
int List<T>::GetListSize() {
	return size;
}

template <typename T>
bool List<T>::search(T data) {
	Node<T>* tempNode = head;

	while (tempNode != NULL) {
		if (tempNode->data == data) {
			return true;
		}
		else {
			tempNode = tempNode->nextNode;
		}
	}
	return false;
}

template <typename T>
void List<T>::remove(T data) {
	// Reference https://www.tutorialspoint.com/learn_c_by_examples/remove_data_from_doubly_linked_list.htm
	// I had issues with my removal so eventually found this website that helped me 
	// find what I was doing wrong
	Node<T>* tempNode = head;
	Node<T>* tempPrevNode = NULL;

	if (head == NULL) {
		// we cant delete from a NULL pointer so return
		return;
	}

	if (head->data == data) {
		--size;
		if (head->nextNode != NULL) {
			head = head->nextNode;			
			return;
		}
		else {
			// Since there are no more nodes
			head = NULL;
			return;
		}

	} else if ((head->data != data) && 
		(head->nextNode == NULL)) {
		// Did not find the data in here so will just return
		return;
	}


	while ((tempNode->nextNode != NULL) &&
	       (tempNode->data != data)) {
		// Keep searching till you find it
		tempPrevNode = tempNode;
		tempNode = tempNode->nextNode;		
	}

	if (tempNode->data == data) {
		tempPrevNode->nextNode = tempPrevNode->nextNode->nextNode;

		if (tempPrevNode->nextNode != NULL) { 
			// This makes the next nodes prev point back
			tempPrevNode->nextNode->prevNode = tempPrevNode;
		}
		else {
			tail = tempPrevNode;
		}

		--size;
		free(tempNode);
	}
	else {
		// Did not find it in this list so just return
		--size;
	}
}

template <typename T>
List<T>::~List() {
	Node<T> tempNode;

	while (!isEmpty()) {
		tempNode = popHead();
	}
}
#endif
