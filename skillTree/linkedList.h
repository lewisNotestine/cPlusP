#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "nodeType.h"
#include "linkedListIterator.h"
#include <cassert>

template <class Type>
class linkedList {
public: 

	const linkedList<Type>& operator=(const linkedList<Type>&);
	//overload assignment operator

	void initializeList();
	//initialize list to an empty state.
	//POST:  first_ = 0, last_ = 0, count_ = 0

	bool isEmptyList() const;
	//Determine whether the list is empty.
	//PRE: none.
	//POST: returns true if empty, false otherwise.
	
	void print() const;
	//output data contained in each node.

	int length() const;
	//returns count_.

	void destroyList();
	//Delete all nodes in list.

	Type front() const;
	//returns first element in list.

	Type back() const;
	//returns last element in list.

	nodeType<Type>* getFirstNode() const;
	//returns pointer to first node in list.

	nodeType<Type>* getLastNode() const;
	//returns pointer to last node in list.

	virtual bool search(const Type& searchItem) const = 0;
	//determines whether searchItem is in list. 
	//PosT:  returns true if item is in list, false otherwise. 

	virtual void insertFirst(const Type& newItem) = 0;
	//inserts an item at the beginning of the list. 
	

	virtual void insertLast(const Type& newItem) = 0;
	//inserts an item at the end of the list.

	virtual bool deleteNode(const Type& deleteItem) = 0;
	//deletes an item determined by child class. 

	void deleteNode(nodeType<Type>* nodeToDelete);
	//deletes list element noted by Node pointer.

	linkedListIterator<Type> begin();
	//Function to return iterator at the beggining of the linked list.

	linkedListIterator<Type> end();
	//Return iterator one element past the end of the list.

	linkedList(); 
	//Default ctor.

	linkedList(const linkedList<Type>& otherList);
	//Copy ctor.

	~linkedList();
	//dtor. 
	//Deletes all nodes from list, POST: list is destroyed.

protected:
	int count_; //count of nodes in list.
	nodeType<Type> *first_;
	nodeType<Type> *last_;

private:
	void copyList(const linkedList<Type>& otherList);
	//returns 

};


//function definitions.
template <class Type> linkedList<Type>::linkedList() {
	first_ = 0;
	last_ = 0;
	count_ = 0;
}

template <class Type> linkedList<Type>::~linkedList() {

}

template <class Type> void linkedList<Type>::destroyList() {

	nodeType<Type>* temp;

	while (first_ != 0) {
		temp = first_;
		first_ = first_->next_;
		delete temp;
	}

	last_ = 0;
	count_ = 0;

	return;
}

template <class Type> bool linkedList<Type>::isEmptyList() const {
	if (count_ == 0) {
		return true;
	} else {
		return false;
	}
}

template <class Type> void linkedList<Type>::initializeList() {
	destroyList();
	return;
}

template <class Type> void deleteNode(nodeType<Type>* nodeToDelete) {
	
}

template <class Type> int linkedList<Type>::length() const {	
	return count_;
}

template <class Type> Type linkedList<Type>::front() const {
	assert(first_ != 0);
	return first_->data_;
}

template <class Type> Type linkedList<Type>::back() const {
	assert(last_ != 0);
	return last_->data_;
}

template <class Type> nodeType<Type>* linkedList<Type>::getFirstNode() const {
	assert(first_ != 0);
	return first_;
}

template <class Type> nodeType<Type>* linkedList<Type>::getLastNode() const {
	assert(last_ != 0);
	return last_;
}

template <class Type> linkedListIterator<Type> linkedList<Type>::begin() {
	linkedListIterator<Type> temp(first_);
	return temp;
}

template <class Type> linkedListIterator<Type> linkedList<Type>::end() {
	linkedListIterator<Type> temp(0);
	return temp;
}

#endif