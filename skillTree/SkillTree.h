#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <iostream>
#include "Skill.h"
#include "generalTree.h"

/*--------------------------------------------------------------------
Skill tree class:  is a generalTree of Skill pointers... 

--------------------------------------------------------------------*/
const int MAX_SKILLS = 3;

class SkillTree : public generalTree<Skill> {
public:
	static std::ostream* SkillTree::myOut_;
	SkillTree();
	SkillTree(const char* treeType);
	~SkillTree();
	
	//creates a skillTree object with the name given by treeType. 
	//Initializes the generalTree base class to have an empty root skill? 
	

	void Display(std::ostream& outStrm);
	void AddSkill(const char* skillName, const char* skillDesc, const int& reqLevel); 
	//Adds a skill at the root of the tree.

	void AddSkill(const char* skillName, const char* skillDesc, const int& reqLevel, const char* preReq);
	//adds a child skill to a place in tree denoted by preReq param.

	Skill* FindSkill(const char* skillName) const;
	//returns skill object, given a node.  has to traverse in correct order to retrieve the skill.

	SkillTree getLeftSkillTree() const;
	SkillTree getRightSkillTree() const;
	//reinstantiations of getLeftTree and getRightTree.  This particular thing may have worked better if we had a compositional rather than inheritance relationship...

protected:
	SkillTree(treeNode<Skill>* newRoot);
	//new root constructor, used in getleftTree, getRightTree.

	void setSkillType(const char* newType);
	const char* getSkillType() const;
	friend void printSkill(Skill* toPrint); 
	friend void printSkill(const int& currentLevel, treeNode<Skill>* currentNode);

private:
	char* skillType_;
	
	void findSkillObj(const char* searchKey, Skill*& skillToFind) const;
	//finds a Skill based on object param, to be passed to generalTree traversal algo. 

	treeNode<Skill>* findSkillNode(treeNode<Skill>* rootNode, const char* skillName) const;
	//same as findSkill but returns a treeNode instead of a Skill obj. 

	treeNode<Skill>* search(treeNode<Skill>* rootNode, const char* searchName, treeNode<Skill>*& outNode) const;

	bool addChildSkill(treeNode<Skill>*& placeToAdd, Skill*& childToAdd, treeNode<Skill>*& trailingNode, int& childCount); 

	void dummyFunct(Skill* dummySkill);
	//just something to pass to inOrder...	

	//traversal functions assigning values to their parms (ref ptrs).
	//void preOrder(treeNode<Skill>* treeRoot, void (*visitFunct)(Skill*&)) ; 
	//traverses tree and applies visitFunct to each data item ... 

	//void postOrder(treeNode<Skill>* treeRoot, void (*visitFunct)(Skill*&)) ; 
	//traverses tree and applies visitFunct to each data item ... 
	
	//void inOrder(treeNode<Skill>* treeRoot, void  (*visitFunct)(Skill*&)) ; 
	//traverses tree and applies visitFunct to each data item... ;
};

#endif