#include "SkillTree.h"
#include <iostream>

using namespace std;

ostream* SkillTree::myOut_ = 0;

SkillTree::SkillTree() : generalTree<Skill>() {
	skillType_ = 0;
	maxChildren_ = MAX_SKILLS;
}

SkillTree::SkillTree(const char* treeType) : generalTree<Skill>() {
	int typeLen = strlen(treeType) + 1;
	skillType_ = new char[typeLen];

	strcpy_s(skillType_, typeLen, treeType);
	maxChildren_ = MAX_SKILLS;
}

SkillTree::~SkillTree() {
	if (skillType_ != 0) {
		delete [] skillType_;
		skillType_ = 0;
	}
}

void SkillTree::Display(std::ostream& outStrm) {
	//TODO:  make each node Print itself, then make a recursive call to a print function for each of its children...
	int currentLevel = 0;

	//if (SkillTree::myOut_ == 0) {
		SkillTree::myOut_ = &outStrm;
	//}

	*myOut_ << "Skill Tree: " << skillType_ << endl;

	if (rootPtr() == 0) {
		*myOut_ << "  Empty" << endl;
	} else {
		//inOrder(rootPtr(), printSkill);
		printSkill(currentLevel, rootPtr());
	}
	return;
}

void printSkill(Skill* toPrint) {
	std::ostream* newOut = SkillTree::myOut_;
	toPrint->setOstream(SkillTree::myOut_);
	toPrint->Display();
	return;
}

void printSkill(const int& currentLevel, treeNode<Skill>* currentNode) {

	//Do this first always.
	//currentLevel starts at 0
	//indent correctly. Don't indent for 0 level.  
	if (currentNode != 0) {
		for (int i = 0; i < currentLevel; i++) {
			*(SkillTree::myOut_) << "  ";
		}
		currentNode->getData()->setOstream(SkillTree::myOut_);
		currentNode->getData()->Display();
	}

	if (currentNode != 0 && currentNode->getChildNode() != 0) {		
		printSkill(currentLevel+1, currentNode->getChildNode());
	} 
	
	if (currentNode != 0 && currentNode->getSiblingNode() != 0) {
		printSkill(currentLevel, currentNode->getSiblingNode());
	} 


	return;
}


void SkillTree::AddSkill(const char* skillName, const char* skillDesc, const int& reqLevel) {
	//adds root.
	treeNode<Skill>* oldRoot = rootPtr();
	treeNode<Skill>* newRoot = 0;

	Skill* newSkill = new Skill(skillName, skillDesc, reqLevel); 
	newSkill->setOstream(this->myOut_);
	newRoot = new treeNode<Skill>(newSkill, oldRoot, 0); //TODO: eventually hide treeNode from SkillTree, make it exposed to generalTree only. 
	setRootPtr(newRoot);

	return;
}

//This is where we add our big recursive algo.
void SkillTree::AddSkill(const char* skillName, const char* skillDesc, const int& reqLevel, const char* preReq) {
	treeNode<Skill>* testNode;
	treeNode<Skill>* rootToAdd;
	int numChildren = 0;
	bool success = false;
	Skill* newSkill = new Skill(skillName, skillDesc, reqLevel, preReq);
	//First, verify that there isn't already a skill node with that name. 

	testNode = findSkillNode(rootPtr(), skillName);

	if (testNode != 0) {
		*myOut_ << "cannot add skill, there is already a skill in the tree named " << skillName << endl;
	} else {
		//Next, need to traverse tree to appropriate node, given by preReq.
		rootToAdd = findSkillNode(rootPtr(), preReq);
		if (rootToAdd != 0) {

			//if (rootToAdd->getChildData() == 0) // add the  
			//Next, try to add a child node at location traversed to. 
		    success = addChildSkill(rootToAdd, newSkill, rootToAdd, numChildren);
		}
	}

	if (!success) {
		delete newSkill;
		newSkill = 0;
	} 
}


//TODO:  This implementation could be a bit better. 
Skill* SkillTree::FindSkill(const char* skillName) const {
	return findSkillNode(rootPtr(), skillName)->getData();


	//treeNode<Skill>* leftPtr = 0;
	//treeNode<Skill>* rightPtr = 0;

	//Skill* leftResult = 0;
	//Skill* rightResult = 0;

	//bool foundSkill = (strcmp(getRootData()->getName(), skillName) == 0);

	//if (strcmp(getRootData()->getName(), skillName) == 0) {  //Base case 1. Item found.
	//	return this->getRootData();
	//} else { //search left, right Skills. 
	//	getChildPtrs(rootPtr(), leftPtr, rightPtr);

	//	if (leftPtr != 0) { 
	//		//return FindSkill(this->getLeftSkillTree().getRootData()->getName());
	//		leftResult = this->getLeftSkillTree().FindSkill(skillName);
	//		if (strcmp(leftResult->getName(), skillName) == 0) {
	//			return leftResult;
	//		}
	//	} else if (rightPtr != 0) {
	//		rightResult = this->getRightSkillTree().FindSkill(skillName);
	//		if (strcmp(rightResult->getName(), skillName) == 0) {
	//			return rightResult;
	//		}
	//		//return FindSkill(this->getRightSkillTree().getRootData()->getName());
	//	} else { //Base case 2: exhausted all items, can't find skill. 
	//		return 0;
	//	}
	//}
	//return 0; 
}

//TODO: finish this:
//there's some problem with this funct...

SkillTree SkillTree::getLeftSkillTree() const {
	treeNode<Skill>* subTrPtr;
	treeNode<Skill>* rightPtr;
	treeNode<Skill>* leftPtr;

	getChildPtrs(rootPtr(), leftPtr, rightPtr);

	if (isEmpty()) {
		return SkillTree();
	} else {
		copyTree(leftPtr, subTrPtr);
		return SkillTree(subTrPtr);
	}
}

SkillTree SkillTree::getRightSkillTree() const {
	treeNode<Skill>* subTrPtr;
	treeNode<Skill>* rightPtr;
	treeNode<Skill>* leftPtr;

	getChildPtrs(rootPtr(), leftPtr, rightPtr);

	if (isEmpty()) {
		return SkillTree();
	} else {
		copyTree(rightPtr, subTrPtr);
		return SkillTree(subTrPtr);
	}
}

SkillTree::SkillTree(treeNode<Skill>* newRoot) {
	skillType_ = 0;
	setRootPtr(newRoot);
	setSkillType(newRoot->getData()->getName());
}

void SkillTree::setSkillType(const char* newType) {
	if (skillType_ != 0) {
		delete [] skillType_;
		skillType_ = 0;
	}
	
	int typeLen = strlen(newType) + 1;
	skillType_ = new char[typeLen];
	strcpy_s(skillType_, typeLen, newType);
}

const char* SkillTree::getSkillType() const {
	return skillType_;
}

void SkillTree::findSkillObj(const char* searchKey, Skill*& skillToFind) const {
	Skill*	thisSkill = getRootData();
	skillToFind = 0;
	bool foundSkill = (strcmp(thisSkill->getName(), searchKey) == 0);
	
	if (foundSkill) {
		skillToFind = thisSkill;
	}

	return;	
} 

void SkillTree::dummyFunct(Skill* dummySkill) {
	return;
}

//versions of the traversal algorithms...
//void SkillTree::inOrder(treeNode<Skill>* treeRoot, void  (*visitFunct)(Skill*&)) {
//	if (treeRoot != 0) {		
//		inOrder(treeRoot->getChildNode(), visitFunct);
//		visitFunct(treeRoot->getData());
//		inOrder(treeRoot->getSiblingNode(), visitFunct);
//	} 
//	return;
//} 


//This could be much better...
treeNode<Skill>* SkillTree::findSkillNode(treeNode<Skill>* rootNode, const char* skillName) const {
		
	treeNode<Skill>* curntPtr = rootNode;
	treeNode<Skill>* leftPtr = 0;
	treeNode<Skill>* rightPtr = 0;

	treeNode<Skill>* retVal = 0;

	getChildPtrs(rootNode, leftPtr, rightPtr);

	if (leftPtr != 0 && strcmp(leftPtr->getData()->getName(), skillName) == 0) { //basecase A. left data matches key.
		retVal = leftPtr;
	} else if (rightPtr != 0 && strcmp(rightPtr->getData()->getName(), skillName) == 0) { //basecase b.  right data matches key.
		retVal = rightPtr;
	} else if (strcmp(rootNode->getData()->getName(), skillName) == 0){		//basecase C. rootnode matches key.
		retVal = rootNode;
	} else { // general case.  Keep looking, left then right.
		if (rootNode->getChildNode() != 0) {
			retVal = findSkillNode(rootNode->getChildNode(), skillName);
		}

		if (retVal == 0) {
			if (rootNode->getSiblingNode() != 0) {
				retVal = findSkillNode(rootNode->getSiblingNode(), skillName);
			}
		}
	}

	return retVal;
}


treeNode<Skill>* SkillTree::search(treeNode<Skill>* rootNode, const char* searchName, treeNode<Skill>*& outNode) const {
	if (rootNode == 0) { // base case 1. item not found. return 0. 
		return 0; 
	} else {
		return 0;
	}
}

//TODO: put this in generalTree!
bool SkillTree::addChildSkill(treeNode<Skill>*& placeToAdd, Skill*& childToAdd, treeNode<Skill>*& trailingNode, int& childCount) {
	treeNode<Skill>* leftPtr;
	treeNode<Skill>* rightPtr;
	//treeNode<Skill>* ptrNode = new treeNode<Skill>;
	//ptrNode = placeToAdd;
	
	
	bool success = false;
	
	//case 1: place's child is empty, first run through.
	if (placeToAdd->getChildNode() == 0 && childCount == 0) {
		placeToAdd->attachChild(new treeNode<Skill>(childToAdd, 0, 0));
		success = true;
	} else if (childCount >0 && childCount < maxChildren_ && placeToAdd->getSiblingNode() == 0) {
		placeToAdd->attachSibling(new treeNode<Skill>(childToAdd, 0, 0));
		success = true;
	} else if (childCount == 0) { // move to the child node.
		placeToAdd = placeToAdd->getChildNode();
		success = addChildSkill(placeToAdd, childToAdd, placeToAdd, ++childCount);
	} else if (childCount >= maxChildren_){
		success = false;
	} else { //move to the sibling node.
		placeToAdd = placeToAdd->getSiblingNode();
		success = addChildSkill(placeToAdd, childToAdd, placeToAdd, ++childCount);
	}
		
	return success;
}