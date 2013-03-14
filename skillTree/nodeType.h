#ifndef NODETYPE_H
#define NODETYPE_H

#include <iostream>

using namespace std;

template <class Type>
struct nodeType {
	Type data_;
	nodeType<Type> *next_;
};

#endif