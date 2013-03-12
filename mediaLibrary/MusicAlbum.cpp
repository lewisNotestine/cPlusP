#include "memoryleakdetect.h"		// needs to be first #include in the .cpp file
#include "MusicAlbum.h"

const string MusicAlbum::MEDIA_TYPE = "Music Album";
const string MusicAlbum::DIV_TYPE = "songs";
const string MusicAlbum::CREATOR_TYPE = "band";
const string MusicAlbum::MEMBERS = "members";

string MusicAlbum::getMediaTypeName() {
	return MEDIA_TYPE;
}

MusicAlbum::MusicAlbum(void) : Item()
{

}

MusicAlbum::MusicAlbum(const string& newTitle) : Item(newTitle)
{
	
}

MusicAlbum::MusicAlbum(const string& newTitle, const string& newCreator, const int& newDivs) : Item(newTitle, newCreator, newDivs)
{

}

MusicAlbum::~MusicAlbum(void)
{
}

void MusicAlbum::initMbrs() {
	
}

string MusicAlbum::toString() const {
	string retVal = this->getClassHeader() + "\n";
	retVal += this->getCreatorAndDivs() + "\n";
	retVal += getEntryRow(getMbrType(), printMbrs()) + "\n";
	retVal += this->getTitleAndKeywds();

	return retVal;
}

//TODO: maybe there's a better way to print things.
string MusicAlbum::printMbrs() const {
	set<string>::iterator mbrIter;
	string retVal = "";
	
	unsigned int outCount = 0;

	for (mbrIter = bandMembers.begin(); mbrIter != bandMembers.end(); mbrIter++) {
		retVal += *mbrIter;
		outCount++;
		if (outCount < bandMembers.size()) { //for every item except last one...
			retVal += ", "; 
		}
	}
	
	return retVal;
}


//Public functions.

string MusicAlbum::getMediaType() const {
	return MusicAlbum::MEDIA_TYPE;
}

string MusicAlbum::getDivType() const {
	return MusicAlbum::DIV_TYPE;
}

string MusicAlbum::getCreatorType() const {
	return MusicAlbum::CREATOR_TYPE;
}


string MusicAlbum::getMbrType() const {
	return MusicAlbum::MEMBERS;
}

string MusicAlbum::getBand() const {
	return getCreator();
}

bool MusicAlbum::hasBandMember(const string& qryMbr) const {
	set<string>::iterator findVal;
	findVal = bandMembers.find(qryMbr);

	if (findVal == bandMembers.end()) {
		return false;
	} else {
		return true;
	}
}

set<string> MusicAlbum::getBandMembers() const {
	return bandMembers;
}

void MusicAlbum::setBand(const string& newBand) {
	setCreator(newBand);
}

void MusicAlbum::addBandMembers(const int& nArgs, ...) {
	va_list varargs;
	va_start(varargs, nArgs);
	string eachMbr;

	for (int i = 0; i < nArgs; i++) {
		eachMbr = va_arg(varargs, string);
		bandMembers.insert(eachMbr);
	}

	va_end(varargs);
}


void MusicAlbum::setBandMembers(const set<string>& bandMbrs) {
	this->bandMembers = bandMbrs;
	return;
}
