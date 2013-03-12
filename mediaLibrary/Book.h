#pragma once

#include "item.h"

class Book :
	public Item
{
private:
	static const string MEDIA_TYPE;
	static const string DIV_TYPE;
	static const string CREATOR_TYPE;
	
	

public:
	//static string getMediaTypeName() const;
	static string getMediaTypeName();
	Book(void);
	Book(const string& newTitle); //used for comparison by title purposes only.
	Book(const string& newTitle, const string& newCreator, const int& newDivs);
	Book(const string& newTitle, const string& newCreator, const int& newDivs, const int& nKeywds, ...);
	
	//inherited late-binding functs.
	string getMediaType() const;
	string getDivType() const;
	string getCreatorType() const;

	~Book(void);

	string toString() const; 
	string getAuthor() const;
	bool hasAuthor(const string& authorName) const; //returns whether book's author is the given param.	
	void setAuthor(const string& newAuthor);
};

