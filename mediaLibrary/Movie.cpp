#include "memoryleakdetect.h"		// needs to be first #include in the .cpp file
#include "Movie.h"
//STATIC mbrs/methods
const string Movie::MEDIA_TYPE = "Movie";
const string Movie::DIV_TYPE = "scenes";
const string Movie::CREATOR_TYPE = "director";
const string Movie::CAST_TYPE = "cast";

string Movie::getMediaTypeName() {
	return MEDIA_TYPE;
}

Movie::Movie(void) : Item()
{
}

Movie::Movie(const string& movieTitle) : Item(movieTitle)
{

}

Movie::Movie(const string& movieTitle, const string& newDirector, const int& newDivs) : Item(movieTitle, newDirector, newDivs) {

}

Movie::Movie(const string& movieTitle, const string& newDirector, const int& newDivs, const int& nKeywds, ...) 
: cast()
{
	va_list varargs;
	va_start(varargs, nKeywds);

}

Movie::~Movie(void)
{

}

string Movie::getMediaType() const {
	return Movie::MEDIA_TYPE;
}

string Movie::getDivType() const {
	return Movie::DIV_TYPE; 
}

string Movie::getCreatorType() const {
	return Movie::CREATOR_TYPE;
}

string Movie::getCastType() const {
	return Movie::CAST_TYPE;
}

string Movie::printCast() const {
	set<string>::iterator mbrIter;
	string retVal = "";
	
	unsigned int outCount = 0;

	for (mbrIter = cast.begin(); mbrIter != cast.end(); mbrIter++) {
		retVal += *mbrIter;
		outCount++;
		if (outCount < cast.size()) { //for every item except last one...
			retVal += ", "; 
		}
	}
	
	return retVal;
}

string Movie::toString() const {
	string retVal = this->getClassHeader() + "\n";
	retVal += this->getCreatorAndDivs() + "\n";
	retVal += this->getEntryRow(getCastType(), printCast()) + "\n";
	retVal += this->getTitleAndKeywds();
	
	return retVal;
}

set<string> Movie::getCast() const {
	return this->cast;
}


bool Movie::hasActor(const string& actorName) const {
	set<string>::iterator findIter;
	findIter = cast.find(actorName);
	if (findIter == cast.end()) {
		return false;
	} else {
		return true;
	}
}

bool Movie::hasDirector(const string& directorName) const {
	return hasCreator(directorName);
}

void Movie::addCast(const int& nArgs, ...) {
	va_list varargs;
	va_start(varargs, nArgs);
	string eachMbr;

	for (int i = 0; i < nArgs; i++) {
		eachMbr = va_arg(varargs, string);
		cast.insert(eachMbr);
	}
	va_end(varargs);
}

void Movie::setCast(const set<string>& newCast) {
	cast = newCast;
	return;
}

