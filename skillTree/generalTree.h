#ifndef GENERALTREE_H
#define GENERALTREE_H

#include <iostream>
#include <cassert>
#include "treeNode.h"

//NOTE:  DO I even need to use recursion to implement a general tree?
//Can probably implement recursively by using a number of different constructors.  
//Each node will be the root of its own general tree.

template <class dataType>
class generalTree {
public:

	generalTree(); //empty tree.
	generalTree(const dataType* rootItem); //tree with root data given as param.
	generalTree(const dataType* rootItem, generalTree<dataType>& leftTree/*, generalTree& rightTree*/); //TODO:  Don't know if rightTree will wever be there. That may be one reason to implement with generalTree pointers? 
	generalTree(const dataType* rootItem, generalTree<dataType>& leftTree, generalTree<dataType>& rightTree); 
	generalTree(const generalTree<dataType>& otherTree);
	~generalTree(); 
	
	bool isEmpty() const;

	dataType* getRootData() const;
	void	setRootData(const dataType*& newRootData);

	void attachLeft(dataType* newItem);
	void attachRight(dataType* newItem);
	void attachLeftTree(generalTree<dataType>& childTree);
	void attachRightTree(generalTree<dataType>& siblingTree); 

	void detachLeftTree(generalTree<dataType>& childTree); 
	void detachRightTree(generalTree<dataType>& siblingTree); 

	generalTree<dataType> getLeftSubtree() const;
	generalTree<dataType> getRightSubtree() const;

	void preorderTraverse(void (*visitFunct)(dataType*));
	void inorderTraverse(void (*visitFunct)(dataType*));
	void postorderTraverse(void (*visitFunct)(dataType*));

	
	generalTree<dataType>& operator=(const generalTree& rightOper);
	/*------------------------------------------------------------------------------
	These functs added to implement general tree specifically from binarytree base...
	------------------------------------------------------------------------------*/


	//bool addChild (dataType* newData, treeNode<dataType>* placeToAdd);
	//add child to place indicated by placeToAdd (Type GeneralTree).  Basically calls node->AddChild or node->addSibling at the appropriate node.
	//instead of traversing node-by-node, uses recursion to traverse to subordinate trees as children. 
	
	//bool addChild (dataType* newData);
	//Adds an item to the root of the tree. if there is already a root, the new item becomes the root and the previous root becomes its child. 

	//void printNodes() const;
	//outputs all the data of all the nodes using an ostream object.  requires << operator of dataType to be overloaded.
	//TODO: This may not work if we're using dataType* pointers, because operators can't be overloaded for pointers.


protected:
	
	generalTree(treeNode<dataType>* nodePtr);	//protected ctor. 
	void copyTree(treeNode<dataType>* treePtr, treeNode<dataType>*& newTreePtr) const; 
	void destroyTree(treeNode<dataType>*& treePtr);
	void clearAll(treeNode<dataType>*& rootPtr);
	treeNode<dataType>* rootPtr() const;
	void setRootPtr(treeNode<dataType>* newRoot);
	
	void attachHere(treeNode<dataType>*& placeHere, dataType* newData);

	void getChildPtrs(treeNode<dataType>* nodePtr, 
		treeNode<dataType>*& leftChildPtr, 
		treeNode<dataType>*& rightChildPtr) const;

	treeNode<dataType>* getLeftPtr(treeNode<dataType>* nodePtr) const;
	treeNode<dataType>* getRightPtr(treeNode<dataType>* nodePtr) const;

	void setChildPtrs(treeNode<dataType>* nodePtr, 
		treeNode<dataType>* leftChildPtr, 
		treeNode<dataType>* rightChildPtr);

	void preOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(dataType*)) ; 
	//traverses tree and applies visitFunct to each data item ... 

	void postOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(dataType*)) ; 
	//traverses tree and applies visitFunct to each data item ... 
	
	void inOrder(treeNode<dataType>* treeRoot, void  (*visitFunct)(dataType*)) ; 
	//traverses tree and applies visitFunct to each data item... ;


	//"SEARCH" VERSIONS OF TRAVERSAL FUNCTIONS...
	void preOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(const char*, dataType*&)) ; 
	//traverses tree and applies visitFunct to each data item ... 

	void postOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(const char*, dataType*&)) ; 
	//traverses tree and applies visitFunct to each data item ... 
	
	void inOrder(treeNode<dataType>* treeRoot, void  (*visitFunct)(const char*, dataType*&)) ; 
	//traverses tree and applies visitFunct to each data item... ;



	/* ------------------------------------------------------------------
	functs specific to general trees.  My defined... 
	/* ------------------------------------------------------------------*/
	dataType* findItem(const char* itemKey) const;
	//returns dataType pointer based on char* searchKey.  
	
	bool hasChild() const;
	//returns whether the childNode of the current tree is occupied (true if yes). 

	/*-------------------------------MY OWN STUFF-----------------------*/
	int	maxDepth_;		//maximum depth of a tree. Default and upper bound is maximum domain of int type.
	int maxChildren_;	//max number of children per node.

	bool addRoot (dataType* newData); 
	//add a new child to root of tree (default);

	bool addSibling(dataType* newData);
	//adds a sibling to the current tree

	//void printData(dataType* printData) const;
	//outputs the data from a data member through the object's output stream...
	//TODO: May have to either put this in the SkillTree class or use a non-operator function to do this because we are using dataType pointers rather than dataType objects.


private:
	
	treeNode<dataType>* root_;

};


/*------------------FUNCTION DEFINITIONS------------*/

template <class dataType> generalTree<dataType>::generalTree() {
	root_ = 0;
	//root_->leftChild_ = 0;
	//root_->rightSibling_ = 0;
}

template <class dataType> generalTree<dataType>::generalTree(const dataType* rootItem) { //tree with root data given as param.
	root_ = new treeNode<dataType>(rootItem, 0, 0);
}

template <class dataType> generalTree<dataType>::generalTree(const dataType* rootItem, generalTree& leftTree ) {
	root_ = new treeNode<dataType>(rootItem, 0, 0);
	attachLeftTree(leftTree);
}

template <class dataType> generalTree<dataType>::generalTree(const dataType* rootItem, generalTree& leftTree, generalTree& rightTree) { 
	root_ = new treeNode<dataType>(rootItem, 0, 0);
	attachLeftTree(leftTree);
	attachRightTree(rightTree);
}

template <class dataType> generalTree<dataType>::generalTree(const generalTree& otherTree) {
	copyTree(otherTree.root_, root_);
}

template <class dataType> generalTree<dataType>::generalTree(treeNode<dataType>* rootNode) {
	root_ = rootNode;
}

template <class dataType> generalTree<dataType>::~generalTree() {
	destroyTree(root_);
}

template <class dataType> bool generalTree<dataType>::isEmpty() const {
	return (root_ == 0);
}

template <class dataType> dataType* generalTree<dataType>::getRootData() const {
	if (!isEmpty()) {
		return root_->data_;
	} else {
		return 0;
	}
}

template <class dataType> void generalTree<dataType>::setRootData(const dataType*& newItem) {
	if (!isEmpty) {
		root_->data_ = newItem;
	} else {
		root_ = new treeNode<dataType>(newItem, 0, 0);
	}

	return;
}

template <class dataType> void generalTree<dataType>::attachLeft(dataType* newItem) {
	if (!isEmpty() && root_->leftChild_ == 0) {
		root_->leftChild_ = new treeNode<dataType>(newItem, 0, 0);
	}
	return;
}

template <class dataType> void generalTree<dataType>::attachRight(dataType* newItem) {
	if (!isEmpty() && root_->rightSibling_ == 0) {
		root_->rightSibling_ = new treeNode<dataType>(newItem, 0, 0);
	}
	return;
}

template <class dataType> 
void generalTree<dataType>::attachHere(treeNode<dataType>*& placeHere, dataType* newData) {
	if (placeHere == 0) {
		placeHere = new treeNode<dataType>(newData, 0, 0);
	}
	return;
}

template <class dataType> void generalTree<dataType>::attachLeftTree(generalTree<dataType>& childTree) {
	if (!isEmpty() && root_->leftChild_ == 0) {
		root_->leftChild_ = childTree.root_;
		childTree.root_ = 0;
	}
	return;
}

template <class dataType> void generalTree<dataType>::attachRightTree(generalTree<dataType>& siblingTree) {
	if (!isEmpty() && root_->rightSibling_ == 0) {
		root_->rightSibling_ = siblingTree.root_;
		siblingTree.root_ = 0;
	}
	return;
}

template <class dataType> 
void generalTree<dataType>::detachLeftTree(generalTree<dataType>& childTree) {
	if (!isEmpty()) {
		childTree = generalTree(root_->leftChild_);
		root_->leftChild_ = 0; 
	}
	return;
}

template <class dataType> 
void generalTree<dataType>::detachRightTree(generalTree<dataType>& siblingTree) {
	if (!isEmpty()) {
		siblingTree = generalTree(root_->rightSibling_);
		root_->rightSibling_ = 0; 
	}
	return;
}


template <class dataType> 
generalTree<dataType> generalTree<dataType>::getLeftSubtree() const {
	treeNode<dataType>* subTrPtr;

	if (isEmpty()) {
		return generalTree<dataType>();
	} else {
		copyTree(root_->leftChild_, subTrPtr);
		return generalTree<dataType>(subTrPtr);
	}
}

template <class dataType>
generalTree<dataType> generalTree<dataType>::getRightSubtree() const {
	treeNode<dataType>* subTrPtr;

	if (isEmpty()) {
		return generalTree<dataType>();
	} else {
		copyTree(root_->rightSibling_, subTrPtr);
		return generalTree<dataType>(subTrPtr);
	}
}

template <class dataType>
void generalTree<dataType>::preorderTraverse(void (*visitFunct)(dataType*)) {
	preOrder(root_, visitFunct);
	return;
}

template <class dataType>
void generalTree<dataType>::inorderTraverse(void (*visitFunct)(dataType*)) {
	inOrder(root_, visitFunct);
	return;
}

template <class dataType>
void generalTree<dataType>::postorderTraverse(void (*visitFunct)(dataType*)) {
	postOrder(root_, visitFunct);
	return;
}

template <class dataType>
void generalTree<dataType>::copyTree(treeNode<dataType>* treePtr, treeNode<dataType>*& newTreePtr) const {
	if (treePtr != 0) {
		newTreePtr = new treeNode<dataType>(treePtr->data_, 0, 0);
		copyTree(treePtr->leftChild_, newTreePtr->leftChild_);
		copyTree(treePtr->rightSibling_, newTreePtr->rightSibling_);
	}

	return;
}


template <class dataType>
void generalTree<dataType>::destroyTree(treeNode<dataType>*& treePtr) {
	
	if (treePtr != 0) {
		destroyTree(treePtr->leftChild_);
		destroyTree(treePtr->rightSibling_);
		delete treePtr;
		treePtr = 0;
	}
	
	return;
}


template <class dataType> 
treeNode<dataType>* generalTree<dataType>::rootPtr() const {
	return root_;
}

template <class dataType>
void generalTree<dataType>::setRootPtr(treeNode<dataType>* newRoot) {
	root_ = newRoot;
}

template <class dataType>
void generalTree<dataType>::getChildPtrs(treeNode<dataType>* nodePtr,
	treeNode<dataType>*& leftPtr,
	treeNode<dataType>*& rightPtr) const 
{
	leftPtr = nodePtr->leftChild_;
	rightPtr = nodePtr->rightSibling_;
	return;
}

template <class dataType>
treeNode<dataType>* generalTree<dataType>::getLeftPtr(treeNode<dataType>* nodePtr) const {
	return nodePtr->leftChild_;
}

template <class dataType>
treeNode<dataType>* generalTree<dataType>::getRightPtr(treeNode<dataType>* nodePtr) const {
	return nodePtr->rightSibling_;
}

template <class dataType>
void generalTree<dataType>::setChildPtrs(treeNode<dataType>* nodePtr,
	treeNode<dataType>* leftPtr,
	treeNode<dataType>* rightPtr) 
{
	nodePtr->leftChild_ = leftPtr;
	nodePtr->rightSibling_ = rightPtr;
	return;
}


template <class dataType>
void generalTree<dataType>::preOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(dataType*)) {
	if (treeRoot != 0) {
		visitFunct(treeRoot->data_);
		preOrder(treeRoot->getChildNode(), visitFunct);
		preOrder(treeRoot->getSiblingNode(), visitFunct);
	} 
	return;
}

template <class dataType>
void generalTree<dataType>::inOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(dataType*)) {
	if (treeRoot != 0) {		
		inOrder(treeRoot->getChildNode(), visitFunct);
		visitFunct(treeRoot->data_);
		inOrder(treeRoot->getSiblingNode(), visitFunct);
	} 
	return;
}


template <class dataType>
void generalTree<dataType>::postOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(dataType*)) {
	if (treeRoot != 0) {
		postOrder(treeRoot->getChildNode(), visitFunct);
		postOrder(treeRoot->getSiblingNode(), visitFunct);
		visitFunct(treeRoot->data_);
	}

	return;
}



//PASS-BY-REFERENCE VERSIONS OF TRAVERSAL FUNCTIONS...
template <class dataType>
void generalTree<dataType>::preOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(const char*, dataType*&)) {
	if (treeRoot != 0) {
		visitFunct(treeRoot->data_);
		preOrder(treeRoot->getChildNode(), visitFunct);
		preOrder(treeRoot->getSiblingNode(), visitFunct);
	} 
	return;
}

template <class dataType>
void generalTree<dataType>::inOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(const char*, dataType*&)) {
	if (treeRoot != 0) {
		inOrder(treeRoot->getChildNode(), visitFunct);
		visitFunct(treeRoot->data_);
		inOrder(treeRoot->getSiblingNode(), visitFunct);
	} 
	return;
}

	
template <class dataType>
void generalTree<dataType>::postOrder(treeNode<dataType>* treeRoot, void (*visitFunct)(const char*, dataType*&)) {
	if (treeRoot != 0) {
		postOrder(treeRoot->getChildNode(), visitFunct);
		postOrder(treeRoot->getSiblingNode(), visitFunct);
		visitFunct(treeRoot->data_);
	} 
	return;
}

template <class dataType>
bool generalTree<dataType>::addRoot(dataType* newData) {
	
}

/*------------------END BINTREE STUFF--------------*/

/*MY OWN STUFF (NOT PART OF BINTREE)*/


/*----------------------------------------------------------------------------------
TODO: Implement addChild() recursively!  
Pass char* of parent skill to the recursive algo and check in each pass of the traversal.  
if (currentNode->name == parentNode->name) pass recursive call to child (parentNOde is the name given in the parameter!)
else pass to sibling.   

I have to put this in skillTree!

----------------------------------------------------------------------------------*/
//template <class dataType> bool generalTree<dataType>::addChild(dataType* newData, treeNode<dataType>* placeToAdd) {
//	if (placeToAdd == 0) { //base case
//		placeToAdd = new treeNode<dataType>(newData, 0, 0); //add child with null sibling/child.
//	} else if (newData == placeToAdd->data_) { //case where this is the same 
//	
//	}
//} 

template <class dataType> bool generalTree<dataType>::hasChild() const {
	return (!(root_->getChildNode() == 0));
}


template <class dataType> void generalTree<dataType>::clearAll(treeNode<dataType>*& rootPtr) {
	if (rootPtr != 0) {
		if (rootPtr->getChildNode() != 0) {
			clearAll(rootPtr->getChildNode());
		}

		if (rootPtr->getSiblingNode() != 0) {
			clearAll(rootPtr->getSiblingNode());
		}

		delete rootPtr;
		rootPtr = 0;
	}

	return;
}

//template <class dataType>
//bool generalTree<dataType>::addChild (dataType* newData) {
//	bool retVal = false;
//	
//	if (this->root_ != 0) {
//		
//	}
//
//	return retVal;
//}

//template <class dataType>
//void generalTree<dataType>::printNodes() const {
//	preOrder(root_, printData(root_->data_));	
//	return;
//}
//
//template <class dataType> void generalTree<dataType>::printData(dataType* printData) const {
//	cout << printData;
//}


#endif
