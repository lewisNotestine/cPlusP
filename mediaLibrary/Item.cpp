#include "memoryleakdetect.h"		// needs to be first #include in the .cpp file
#include "Item.h"


//static CLASS variables/methods:
string Item::classMediaType = "";		//initialize this to an empty string.
const string Item::TITLE = "title";
const string Item::KEYWORDS = "keywords";


string Item::getMediaTypeName() {
	return "";
}

//TODO: make the inheritance work more as specified in the original assignment3; (i.e., collection of members etc)?
Item::Item(const string& newTitle, const string& newCreator) :
title(newTitle),
	creator(newCreator)
{
	// your code here
}

Item::Item(const string& newTitle, const string& newCreator, const int& newDivs) :  
title(newTitle),
	creator(newCreator),
	contentDivs(newDivs)
{

}

Item::Item(const string& newTitle, const string& newCreator, const int& newDivs, const int& nKeywds, ...) :
title(newTitle), 
	creator(newCreator),
	contentDivs(newDivs)

{
	//initialize vararg keywords.	
	va_list varargs;
	va_start(varargs, nKeywds);
	
	for (int i = 0; i < nKeywds; i++) {
		keyWords.insert(va_arg(varargs, string));	
	}

	va_end(varargs);
}

Item::Item(const string& newTitle) :
title(newTitle)
{

}


Item::Item()
{
	
}

Item::~Item()
{
	// your code here
}

string Item::getTitle() const {
	return this->title;
}

//string Item::getCreatorType() const {
//	return this->creatorType;
//} 
//
//string Item::getDivType() const {
//	return divType;
//}
//
//string Item::getMediaType() const {
//	return mediaType;
//}

string Item::getCreator() const {
	return creator;
}

set<string> Item::getKeywords() const {
	return this->keyWords;
}



bool Item::hasKeyword(const string& keyWord) const {
	set<string>::iterator keyIter;

	keyIter = keyWords.find(keyWord); //find returns the iter's end if item is not found...
	if (keyIter == keyWords.end()) { 
		return false;
	} else {
		return true;
	}	
}

bool Item::hasCreator(const string& creatorName) const {
	if (creator == creatorName) {
		return true;
	} else {
		return false;
	}
}

string Item::getClassHeader() const {
	string retVal = "-" + this->getMediaType() + "-";
	return retVal;
}

//TODO: update this. 
int Item::getContentDivs() const {
	return this->contentDivs;
}

string Item::outputKeywords() const {
	set<string>::iterator castIter;
	string retVal = "";
	//string currentMember;
	unsigned int outCount = 0;

	for (castIter = keyWords.begin(); castIter != keyWords.end(); castIter++) {
		retVal += *castIter;
		outCount++;
		if (outCount < keyWords.size()) { //for every item except last one...
			retVal += ", "; 
		}

	}
	
	return retVal;
}

string Item::getCreatorAndDivs() const { //virtual because it has to call subClass-defined methods
	string retVal = "";
	char* divChar = new char[10]; //TODO: fix char array.

	_itoa(getContentDivs(), divChar, 10); 
	retVal += getEntryRow(this->getCreatorType(), getCreator()) + '\n';
	retVal += getEntryRow("# " + this->getDivType(), string(divChar));

	delete [] divChar;
	divChar = 0;

	return retVal;
}

string Item::getTitleAndKeywds() const {
	string retVal = "";
	retVal += getEntryRow(TITLE, getTitle()) + "\n";
	retVal += getEntryRow(KEYWORDS, outputKeywords()) + "\n";

	return retVal; 
}

string Item::getEntryRow(string headerCol, string& contentCol) const {
	stringstream strStm;
	string retVal;
	string endl1 = headerCol + ":";
	
	strStm << setw(PRINT_SPACES) << left << endl1;
	
	retVal = strStm.str();
	retVal += contentCol;
	
	return retVal;
}

//MUTATOR Methods
//TODO: make sure that polymorphic calls to this are getting run right!
//void Item::setMediaType(const string& newMediaType) {
//	mediaType = newMediaType;
//	if (classMediaType == "") {
//		classMediaType = newMediaType;
//	}
//	return;
//}
//
//void Item::setDivType(const string& newDivType) {
//	divType = newDivType;
//	return;
//}
//
//void Item::setCreatorType(const string& newCreatorType) {
//	creatorType = newCreatorType;
//	return;
//}

void Item::setTitle(const string& newTitle) {
	title = newTitle;
	return;
}

void Item::setCreator(const string& newCreator) {
	creator = newCreator;
	return;
}

void Item::setKeywords(const set<string>& newKeyWds) {

	return;
}

void Item::addKeyword(const string& wordToAdd) {
	keyWords.insert(wordToAdd);
	return;
}

void Item::addKeywords(const set<string>& newKeyWds) {
	
	return;
}

//string Item::toString() const {
//	string retVal = this->getClassHeader() + "\n";
//	retVal += this->getCreatorAndDivs();
//
//	return retVal;
//}

bool operator<(const Item& i1, const Item& i2) {
	// your code here
	if (i1.getTitle() < i2.getTitle()) {
		return true;
	} else {
		return false;
	}
}

bool operator<(const ItemPtr& ip1, const ItemPtr& ip2)
{
	// your code here
	if (ip1.getPtr()->getTitle() < ip2.getPtr()->getTitle()) {
		return true;
	} else {
		return false;
	}
}

ostream& operator<<(ostream& out, const Item* const item)
{
	// your code here
	string outStr = item->toString();
	out << outStr;
	return out;
}
