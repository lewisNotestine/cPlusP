#ifndef TREENODE_H
#define TREENODE_H

template <class dataType>
class treeNode {
public:
	
	
	
	treeNode();
	treeNode(dataType* dataItem, 
	treeNode<dataType>* leftTree, 
	treeNode<dataType>* rightTree);
	treeNode(treeNode<dataType>* otherNode);
	~treeNode();

	dataType* getData() const;
	bool hasChild() const;

	dataType* getChildData() const;
	dataType* getSiblingData() const;
	treeNode<dataType>* getChildNode() const;
	treeNode<dataType>* getSiblingNode() const;
	void attachChild(treeNode<dataType>* newChild);
	void attachSibling(treeNode<dataType>* newSib);
	treeNode<dataType>*	leftChild_;
	treeNode<dataType>*	rightSibling_;

protected:
	template <class dataType> friend class generalTree;

private:
	
	//assigns tree based on data and left/child, right/Sibling items.  

	dataType* data_; //pointer to a dataType, the content of the node. 

	
	int getChildCount() const;
	

	
	
};

/*---------------BEGIN FUNCTION DEFS---------------*/

template <class dataType>
dataType* treeNode<dataType>::getData() const {
	return data_; 
}

template <class dataType> treeNode<dataType>::treeNode() {
	data_ = 0;
	leftChild_ = 0;
	rightSibling_ = 0;
}

template <class dataType> treeNode<dataType>::treeNode(dataType* dataItem, 
		treeNode<dataType>* leftTree, 
		treeNode<dataType>* rightTree) {
	
	data_ = dataItem;
	leftChild_ = leftTree;
	rightSibling_ = rightTree;
}

template <class dataType>
treeNode<dataType>::treeNode(treeNode<dataType>* otherNode) {
	this->data_ = otherNode->data_;
	this->leftChild_ = otherNode->leftChild_;
	this->rightSibling_ = otherNode->rightSibling_;
}

template <class dataType>
treeNode<dataType>::~treeNode() {
	//if (leftChild_ != 0) {
	//	delete leftChild_;
	//}

	//if (rightSibling_ != 0) {
	//	delete rightSibling_;
	//}

	if (data_ != 0) {
		delete data_;
		data_ = 0;
	}
}


//TODO: not sure if this needs to be implemented; just include node count in tree class? 
template <class dataType> int treeNode<dataType>::getChildCount() const {
	int outCount = 0; 
	return outCount;
}

template <class dataType> treeNode<dataType>* treeNode<dataType>::getChildNode() const {
	if (leftChild_ != 0) {
		return this->leftChild_;
	} else {
		return 0;
	}
}

template <class dataType> treeNode<dataType>* treeNode<dataType>::getSiblingNode() const {
	if (rightSibling_ != 0) {
		return this->rightSibling_;
	} else {
		return 0; 
	}
}

template <class dataType> dataType* treeNode<dataType>::getChildData() const {
	return this->leftChild_->getData();
}

template <class dataType> dataType* treeNode<dataType>::getSiblingData() const {
	return this->rightSibling_->getData();
}

template <class dataType> bool treeNode<dataType>::hasChild() const {
	return (this->getData() != 0);
}

template <class dataType>
void treeNode<dataType>::attachChild(treeNode<dataType>* newChild) {
	if (this->leftChild_ == 0) {
		this->leftChild_ = newChild;
	}
}

template <class dataType>
void treeNode<dataType>::attachSibling(treeNode<dataType>* newSib) {
	if (this->rightSibling_ == 0) {
		this->rightSibling_ = newSib;
	}
}



#endif