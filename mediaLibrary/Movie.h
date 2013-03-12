#pragma once

#include "item.h"

class Movie :
	public Item
{

private:
	static const string MEDIA_TYPE;
	static const string DIV_TYPE;
	static const string CREATOR_TYPE;
	static const string CAST_TYPE;

	set<string> cast;

	string printCast() const;
	
	

public:
	
	static string getMediaTypeName();
	Movie(void);
	Movie(const string& movieTitle);
	Movie(const string& movieTitle, const string& newDirector, const int& newDivs);
	Movie(const string& movieTitle, const string& newDirector, const int& newDivs, const int& nKeywds, ...);
	~Movie(void);

	//inherited late-binding functs.
	string getMediaType() const;
	string getDivType() const;
	string getCreatorType() const;
	//early-bind funct.
	string getCastType() const;

	//TODO: Should C++ objects have a tostring method?
	string toString() const;
	set<string> getCast() const;
	bool hasActor(const string& actorName) const;
	bool hasDirector(const string& directorName) const;
	void addCast(const int& nArgs, ...);	
	void setCast(const set<string>& newCast); 
};

