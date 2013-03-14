#include "Skill.h"

using namespace std;

Skill::Skill() {
	name_ = 0;
	description_ = 0;
	level_ = 0;
	preReq_ = 0;
}

Skill::Skill(const char* name) {
	int nameLen = strlen(name) + 1;
	name_ = new char[nameLen];

	strcpy_s(name_, nameLen, name);
	description_ = 0;
	level_ = 0;
	preReq_ = 0;
}

Skill::Skill(const char* name, const char* desc, const int& level) {
	int nameLen = strlen(name) + 1;
	int descLen = strlen(desc) + 1;

	name_ = new char[nameLen];
	description_ = new char[descLen];

	strcpy_s(name_, nameLen, name);
	strcpy_s(description_, descLen, desc);
	level_ = level;
	preReq_ = 0;	//because the skill is the new root.
}

Skill::Skill(const char* name, const char* desc, const int& level, const char* preReq) {
	int nameLen = strlen(name) + 1;
	int descLen = strlen(desc) + 1;
	int preLen = strlen(preReq) + 1;

	name_ = new char[nameLen];
	description_ = new char[descLen];
	preReq_ = new char[preLen];

	strcpy_s(name_, nameLen, name);
	strcpy_s(description_, descLen, desc);
	level_ = level;
	strcpy_s(preReq_, preLen, preReq);	
}

Skill::~Skill() {
	if (name_ != 0) {
		delete [] name_;
		name_ = 0;
	}

	if (description_ != 0) {
		delete [] description_;
		description_ = 0;
	}

	if (preReq_ != 0) {
		delete [] preReq_;
		preReq_ = 0;
	}
}

//TODO: make this take an ostream parameter per requirements. 
void Skill::Display() const {
	if (name_ != 0) {
		*myOut_ << "  - " << name_ << " -- " << description_ << " [Lvl: " << level_ << "]" << endl;
	} else {
		*myOut_ << "No Skill here!" << endl;
	}
	return;
}

void Skill::setOstream(std::ostream* newOut) {
	myOut_ = newOut;
	return;
}

std::ostream& operator<< (std::ostream& osObject, const Skill& osPotion) {
	//osObject << "Potion of " << osPotion.getTypeStr() << endl;
	return osObject;
}

const char* Skill::getName() const {
	return name_;
}