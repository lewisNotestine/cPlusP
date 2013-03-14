#ifndef SKILL_H
#define SKILL_H

#include <iostream>

class Skill {


public:

	Skill();
	Skill(const char* name); //used for search node only.
	Skill(const char* name, const char* desc, const int& level);
	Skill(const char* name, const char* desc, const int& level, const char* preReq);
	~Skill();
	void Display() const;
	friend std::ostream& operator<< (std::ostream& osObject, const Skill& outSkill); //overloaded << operator.

	const char* getName() const;
	//returns name of skill. 
	const char* getDesc() const;

	void setOstream(std::ostream* newOut);

protected:
private:
	char*	name_;
	char*	description_;
	int		level_;
	char*	preReq_;
	std::ostream* myOut_;
};

#endif