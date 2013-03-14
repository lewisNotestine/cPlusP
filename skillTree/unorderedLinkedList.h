#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include <iostream>
#include "linkedList.h"

template <class Type>
class unorderedLinkedList: public linkedList<Type> {
public:

	unorderedLinkedList();
	unorderedLinkedList(unorderedLinkedList& otherList);
	~unorderedLinkedList();

	bool search(const Type& searchItem) const;
	//determines whether param. item is in the list

	bool getData(const Type& searchItem, Type& returnItem) const;
	//same as search but returns Type.

	bool getData(const Type& searchItem, Type* returnItem) const;
	//same as search but outputs Type pointer param.

	bool getData(const int& dataIndex, Type& returnItem) const;
	//traverses list and returns data at a particular place.

	Type* getData(const Type& searchItem) const;
	//getData that returns Type pointer.

	void insert(const Type& newItem);
	//inserts item at appropriate point in the list.

	void insertFirst(const Type& newItem);
	//inserts at beginning of the list.

	void insertLast(const Type& newItem);
	//inserts item at end of list.

	bool deleteNode(const Type& deleteItem);
	//deletes the node indicated by param.

	int getCount() const;
	//gets the number of items in the list.

	//bool deleteNode(const char* const deleteName);
	//deletes the node indicated by char parm.
	
	
};


//Function defs.
template <class Type> unorderedLinkedList<Type>::unorderedLinkedList() {
}

template <class Type> unorderedLinkedList<Type>::~unorderedLinkedList() {
	destroyList();
}

template <class Type> bool unorderedLinkedList<Type>::search(const Type& searchItem) const {
	bool			found = false;
	nodeType<Type>*	current;

	current = first_;

	while (current != 0 && !found) {
		if (current->data_ == searchItem) {
			found = true;
		} else {
			current = current->next_;
		}
	}

	if (found) {
		found = (current->data_ == searchItem);
	}

	return found;
}

template <class Type> bool unorderedLinkedList<Type>::getData(const Type& searchItem, Type& returnItem) const {
		
	bool			found = false;
	nodeType<Type>*	current;
	Type			noData;

	current = first_;

	while (current != 0 && !found) {
		if (current->data_ >= searchItem) {
			found = true;
		} else {
			current = current->next_;
		}
	}

	//doublecheck.
	if (found) {
		found = (current->data_ == searchItem);
		if (found) {
			//need to have assignment operator for Type!
			returnItem = current->data_; 
		}
	}

	return found;
}

template <class Type> bool unorderedLinkedList<Type>::getData(const Type& searchItem, Type* returnItem) const {
		
	bool			found = false;
	nodeType<Type>*	current;
	//Type*			noData;

	current = first_;

	while (current != 0 && !found) {
		if (current->data_ == searchItem) {
			found = true;
		} else {
			current = current->next_;
		}
	}

	//doublecheck.
	if (found) {
		found = (current->data_ == searchItem);
		if (found) {
			//need to have assignment operator for Type!
			returnItem = &(current->data_); 
		}
	}

	return found;


}

template <class Type> bool unorderedLinkedList<Type>::getData(const int& dataIndex, Type& returnItem) const {
	int iCount = 0; //var for counting iterations.
	nodeType<Type>* current = first_;
	bool			retVal;

	while (iCount <= this->getCount() - 1) {
		if (iCount == dataIndex) {
			returnItem = current->data_;
			retVal = true;
			break;
		} else if (iCount == this->getCount() - 1) { // end of list, no success
			retVal = false;
			break;
		} else {
			current = current->next_;
			iCount++; 
		}		
	}

	return retVal;
}

template <class Type> Type* unorderedLinkedList<Type>::getData(const Type& searchItem) const {
		
	bool			found = false;
	nodeType<Type>*	current;

	current = first_;

	while (current != 0 && !found) {
		if (current->data_ == searchItem) {
			found = true;
		} else {
			current = current->next_;
		}
	}

	//doublecheck.
	if (found) {
		found = (current->data_ == searchItem);
		if (found) {
			//need to have assignment operator for Type!
			return &(current->data_); 
		} else {
			return 0;
		}
	} else {
		return 0; 
	}
}

//TODO: make this so a pointer is inserted.
template <class Type> void unorderedLinkedList<Type>::insert(const Type& newItem) {
	nodeType<Type>	*current;
	nodeType<Type>	*trail;
	nodeType<Type>	*newNode;
	bool			found; //flag for finding item in set. 

	newNode = new nodeType<Type>;  //create the node.
	newNode->data_ = newItem;
	newNode->next_ = 0;

	if (first_ == 0) { // Case 1. list is empty. 
		first_ = newNode;
		last_ = newNode;
		count_++;
	} else {
		current = first_;
		found = false;

		while (current != 0 && !found) {	  //search for 
			if (current->data_ == newItem) {  //condition for insertion in right spot. TODO:  make this based on the comparison of names by overloading the >= operator for the item class. 
				found = true;
			} else {
				trail = current;
				current = current->next_;
			}
		}
			
		if (current == first_) {		//Case 2: item is 
			newNode->next_ = first_;
			first_ = newNode;
			count_++;

		} else {					//Case 3: Insert item at end of list.
			trail->next_ = newNode;
			newNode->next_ = current;

			if (current == 0) {
				last_ = newNode;
			}
			count_++;
		}
	}	

	return;
}

template <class Type> void unorderedLinkedList<Type>::insertFirst(const Type& newItem) {
	nodeType<Type>* newNode;	//Pointer to create new node.
	
	newNode = new nodeType<Type>;
	newNode->data_ = newItem;
	newNode->next_ = first_;
	first_ = newNode;

	count_++;

	if (last_ == 0) {
		last_ = newNode;
	}

	return;
}

template <class Type> void unorderedLinkedList<Type>::insertLast(const Type& newItem) {
	nodeType<Type>* newNode;
	newNode = new nodeType<Type>;
	newNode->data_ = newItem;
	newNode->next_ = 0;

	if (first_ = 0) {
		first_ = newNode;
		last_ = newNode;
		count_++;
	} else {
		last_->next_ = newNode;
		last_ = newNode;
		count_++;
	}

	return;
}

template <class Type> bool unorderedLinkedList<Type>::deleteNode(const Type& deleteItem) {
	nodeType<Type>	*current;
	nodeType<Type>	*trail;
	bool			found = false;

	if (first_ == 0) { // case 1
		cout << "Cannot delete from empty list." << endl;
	} else {
		current = first_;
		//found = false;

		while (current != 0 && !found) { //search the list
			if (current->data_ == deleteItem) {
				found = true;
			} else {
				trail = current;
				current = current->next_;
			}
		}

		if (current == 0) { // case 4
			cout << "The item to be deleted is not in the list." << endl;
		} else {
			if (current->data_ == deleteItem) { //the item to be deleted is in the list.
				if (first_ == current) {
					first_ = first_->next_;

					if (first_ == 0) {
						last_ = 0;
					}

					delete current;
					found = true;

				} else {
					trail->next_ = current->next_;

					if (current == last_) {
						last_ = trail;
					}

					delete current;
					found = true;
				}	
				count_--;

			} else {  //case 4
				cout << "the item to be deleted is not in the list." << endl;
			}
		}
	}
	return found;
}

template <class Type> int unorderedLinkedList<Type>::getCount() const {
	return count_;
}


#endif