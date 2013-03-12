#include "memoryleakdetect.h"		// needs to be first #include in the .cpp file
#include "Book.h"

//STATIC MBRS/Methods
const string Book::MEDIA_TYPE = "Book";
const string Book::DIV_TYPE = "pages";
const string Book::CREATOR_TYPE = "author";

string Book::getMediaTypeName() {
	return MEDIA_TYPE;
}


Book::Book(void) 
{

}

Book::Book(const string& newTitle) : Item(newTitle)
{}

Book::Book(const string& newTitle, const string& newCreator, const int& newDivs) : Item(newTitle, newCreator, newDivs)
{
	
}

//TODO: not sure if this is going to work. watch this one.
//if this doesn't work, just put a protected method in Item that processes keywords and maybe a protected ctor too.
Book::Book(const string& newTitle, const string& newCreator, const int& newDivs, const int& nKeywds, ... ) {

}

Book::~Book(void) {
	
}

string Book::getMediaType() const {
	return MEDIA_TYPE;
}

string Book::getDivType() const {
	return DIV_TYPE;
}
//
string Book::getCreatorType() const {
	return CREATOR_TYPE;
}

string Book::toString() const {
	string retVal = this->getClassHeader() + "\n";
	retVal += this->getCreatorAndDivs() + "\n";
	retVal += this->getTitleAndKeywds();
	return retVal;
}

string Book::getAuthor() const {
	return getCreator();
}

bool Book::hasAuthor(const string& authorName) const {
	return hasCreator(authorName);
}

void Book::setAuthor(const string& newAuthor) {
	setCreator(newAuthor);
}