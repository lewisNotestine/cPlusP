#ifndef H_LINKEDLISTITERATOR
#define H_LINKEDLISTITERATOR

#include "nodeType.h"

template <class Type>
class linkedListIterator {
public:
	linkedListIterator();
	linkedListIterator(nodeType<Type> *ptr);
	
	Type operator*();
	//Overload dereferencing operator
	//POST: sets current to ptr.
	
	linkedListIterator<Type> operator++ ();
	//Overload pre-increment operator.
	//POST:  iterator is advanced to next node.
	
	bool operator== (const linkedListIterator<Type>& right) const;
	//Overload equality oper.
	//Returns true if this is equal to the iterator in parameter. false otherwise.

	bool operator!= (const linkedListIterator<Type>& right) const;
	//Overload inequality oper.
	//Returns true if this is not equal to the iterator in parameter. false otherwise.

private:
	nodeType<Type> *current_;
	//pointer to the current node. 

};


//function defs.
template <class Type> linkedListIterator<Type>::linkedListIterator() {
	current_ = 0;
}

template <class Type> linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr) {
	current_ = ptr;
}

//TODO. verify return type.
template <class Type> Type linkedListIterator<Type>::operator* () {
	return current_->data_;
}

template <class Type> linkedListIterator<Type> linkedListIterator<Type>::operator++ () {
	current_ = current_->next_;
	return *this;	
}

template <class Type> bool linkedListIterator<Type>::operator== (const linkedListIterator<Type>& right) const {
	return (current_ == right.current_);
}

template <class Type> bool linkedListIterator<Type>::operator!= (const linkedListIterator<Type>& right) const {
	return (current_ != right.current_);
}




#endif