#pragma once

#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdarg.h>

using namespace std;

class Item
{

private:
	static string classMediaType; // set by base classes.
	static const int PRINT_SPACES = 11;
	static const string TITLE;
	static const string KEYWORDS;

	string			title;
	string			creator;
	set<string>		keyWords;
	int				contentDivs;


protected:
	
	
	bool hasKeyword(const string& keyWord) const; //Returns whether or not the Item has the keyword given as param.
	bool hasCreator(const string& creatorName) const; //returns whether the item has the creator given by name.	
	virtual string getClassHeader() const;		//returns the class header of the object.	
	
	
	string outputKeywords() const;		//outputs a string representation of the keywords as a comma-delimited list.
	int	getContentDivs() const;			//returns the number of contentDivs(pages etc).
	virtual string getCreatorAndDivs() const;	//returns the string output for the creator and divs.
	string getTitleAndKeywds() const;	//returns the 
	string getEntryRow(string headerCol, string& contentCol) const;

	//void setMediaType(const string& newMediaType);		//sets the media type. Different for each subclass.
	//void setDivType(const string& newDivType);			//sets the div type for the media. 
	//void setCreatorType(const string& newCreatorType);	//sets the creator type for the object.

	void setTitle(const string& newTitle);		//sets the title of the item.
	void setCreator(const string& newCreator);	//sets the creator/artist name of the item.
	void setKeywords(const set<string>& newKeywords);	//sets the keywords to be 
	
	
	void setContentDivs(const int& newContentDivs);		//sets the content divs equal to param.
	
public:
	static string getMediaTypeName();
	//virtual string mediaTypeName() const = 0; //virtual wrapper function for static getMediaTypeName(), returning the class' .  
	string getCreator() const;			//returns the name of the creator/artist.	
	//set<string>	getKeywords() const;	//returns the set of keywords.
	
	virtual string getMediaType() const = 0;		//returns the media type of teh object.
	virtual string getCreatorType() const = 0;		//reutrns the creator type.
	virtual string getDivType() const = 0;			//returns the div type of the object (pages, tracks, etc).
	
	set<string>		getKeywords() const;	//returns the set of keywords.
	void addKeyword(const string& wordToAdd);			//adds a keyword to the list.
	void addKeywords(const set<string>& wordsToAdd);	//adds a collection of keywords to the list.
	Item(const string& title, const string& artist);
	
	Item();
	Item(const string& newTitle);
	Item(const string& newTitle, const string& newCreator, const int& newDivs);
	Item(const string& newTitle, const string& newCreator, const int& newDivs, const int& nKeywds, ...); //std ctor to populate relevant items.
	virtual ~Item();

	string getTitle() const;			//returns the title of the Item.
	virtual string toString() const = 0; //outputs a string representation of the object.
};

// You can't store Item* in an ItemSet, because that would disable the automatic
// sorting that set does. Containers in the C++ STL are designed to store
// INSTANCES, not POINTERS to instances.
//
// Instead we store instances of ItemPtr in the ItemSet defined in Library.h.
// Each instance of ItemPtr contains a pointer to an instance of Item. In this way,
// the container can call operator< for ItemPtr (which can then call operator<
// for Item) to determine the order in which to store the items it's given.
//
// When you add a Book instance to an ItemSet, you can do things like this:
//
//		ItemSet		books;					// defined in Library.h
//		Item		*book = new Book(...);
//
//		books.insert(book);
//
// The STL's set class will internally generate an instance of ItemPtr
// which will contain the pointer to the instance of Book.

class ItemPtr
{
private:
	Item	*ptr;

public:
	ItemPtr(Item *ptr) : ptr(ptr) { }
	Item* getPtr() const { return ptr; }
};

// compare two instances of Item
bool operator<(const Item& i1, const Item& i2);

// compare two instances of ItemPtr
bool operator<(const ItemPtr& ip1, const ItemPtr& ip2);

ostream& operator<<(ostream& out, const Item* const item);


