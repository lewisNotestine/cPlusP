#include "memoryleakdetect.h"		// needs to be first #include in the .cpp file
#include <cstdarg>					// support macros for vararg
#include <iostream>
#include "Library.h"
#include <algorithm>
#include <set>
#include <vector>

//tests a set intersection.
void Library::testIndices(StringSet& testStrSet) {
	int first[] = {5, 10, 15, 20, 25};
	int second[] = {50, 40, 30, 20, 10};
	vector<int> v(10);
	vector<int>::iterator it;

	sort (first, first+5);
	sort (second, second+5);
	
	it = set_intersection(first, first+5, second, second+5, v.begin());


}

//Ctor
Library::Library() : queryPtr(&currentQuery)
{
	initIndices();
}

Library::Library(const Library*& otherLib) {
	//clone other library...
	//copyItemColl(otherLib);
	//copyMap(const_cast<Library*&>(otherLib)->keywordIndex, this->keywordIndex);
	//copyMap(const_cast<Library*&>(otherLib)->artistIndex, this->artistIndex);
	//copyMap(const_cast<Library*&>(otherLib)->memberIndex, this->memberIndex);
	//copyCurrentQuery(otherLib);
}

Library::~Library()
{
	map<string, ItemPtr>::iterator	deleteIter;
	Item*							deleteItem;

	for (deleteIter = itemCollection.begin(); deleteIter != itemCollection.end(); deleteIter++) {
		deleteItem = deleteIter->second.getPtr();	
		delete deleteItem;
		deleteItem = 0;
	}

	if (queryPtr != 0) {
		delete queryPtr;
		queryPtr = 0;
	}
	// your code here
}



// general functions
Library Library::clone() {
	return *this;
}

//keywords here are given as char*...
void Library::addKeywordsForItem(const Item* const item, int nKeywords, ...)
{
	// the code in this function demonstrates how to handle a vararg in C++
	va_list					keywords;
	char*					keyword; 
	string					keyStr;
	Item*					foundItem; //Item to be looked up from the list.
	string					searchItem = item->getTitle();
	pair<string, StringSet> keywdInsertValue;

	map<string, ItemPtr>::iterator searchIter;
	map<string, StringSet>::iterator keywordIter;
	
	// 1. find the NON-CONST item in the library that matches the search key.
	searchIter = itemCollection.find(searchItem);
	
	if (searchIter != itemCollection.end()) {
		foundItem = searchIter->second.getPtr();
		va_start(keywords, nKeywords);
		for (int i = 0; i < nKeywords; i++) {
			keyword = va_arg(keywords, char*);
			keyStr = string(keyword);
			// do something with each keyword
			// 2. add keywords to the non-const item.			
			foundItem->addKeyword(keyStr);
		
			// 3. add the item's title to the keyword index.
			keywordIter = keywordIndex.find(keyStr); // if keyword is already there, add title to keywordINdex
			if (keywordIter != keywordIndex.end()) { 
				keywordIter->second.insert(foundItem->getTitle());
			} else { // if keyword isn't already there.
				keywdInsertValue = pair<string, StringSet>(keyStr, StringSet());
				keywordIndex.insert(keywdInsertValue);
				keywordIndex.at(keyStr).insert(foundItem->getTitle());
			}				
		}
		va_end(keywords);
	}
}

void Library::testItemsForKeyword(string parameter) {
	string keyStr = string(parameter);
	map<string, StringSet>::iterator keywordIter;
	keywordIter = keywordIndex.find(keyStr);
}

const ItemSet* Library::itemsForKeyword(const string& keyword) {	
	map<string, StringSet> searchIdx1 = keywordIndex;
	return searchIndexOne(searchIdx1, keyword);
}

// book-related functions

const Item* Library::addBook(const string& title, const string& author, const int nPages)
{
	Item* newBook = new Book(title, author, nPages);
	if (itemCollection.count(newBook->getTitle()) == 0) {
		itemCollection.insert(pair<string, ItemPtr>(title, newBook));
	} else {
		return 0;
	}

	if (itemCollection.count(newBook->getTitle()) == 0) {
		return 0;
	} else {
		addMediaIndex(newBook);
		addArtistIndex(newBook);

		return newBook;
	}
}

//TODO: This is going to return a bad pointer. Fix.
const ItemSet* Library::booksByAuthor(const string& author) 
{	
	map<string, StringSet> searchIdx1 = mediaIndex;
	map<string, StringSet> searchIdx2 = artistIndex;
	return searchIndexTwo(searchIdx1, Book::getMediaTypeName(), searchIdx2, author);	
}

const ItemSet* Library::books() 
{
	// your code here
	map<string, StringSet>	mediaIdx = mediaIndex;
	return searchIndexOne(mediaIdx, Book::getMediaTypeName());	
}

// music-related functions

const Item* Library::addMusicAlbum(const string& title, const string& band, const int nSongs)
{
	Item* newAlbum = new MusicAlbum(title, band, nSongs);
	if (itemCollection.count(newAlbum->getTitle()) == 0) {
		itemCollection.insert(pair<string, ItemPtr>(title, newAlbum));
	} else {
		return 0;
	}

	if (itemCollection.count(newAlbum->getTitle()) == 0) {
		return 0;
	} else {
		//addKeywordIndex(newBook);
		addMediaIndex(newAlbum);
		addArtistIndex(newAlbum);

		return newAlbum;
	}
}

void Library::addBandMembers(const Item* const musicAlbum, const int nBandMembers, ...)
{
	// the code in this function demonstrates how to handle a vararg in C++
	va_list					mbrArgs;
	string					mbrArg;
	char*					charArg; 
	string					keyStr;
	Item*					foundItem; //Item to be looked up from the list.
	string					searchItem = musicAlbum->getTitle();
	pair<string, StringSet> mbrInsertValue;
	StringSet				outputMbrs;

	map<string, ItemPtr>::iterator searchIter;
	map<string, StringSet>::iterator mbrIter;
	
	// 1. find the NON-CONST item in the library that matches the search key.
	searchIter = itemCollection.find(musicAlbum->getTitle());
	
	if (searchIter != itemCollection.end()) {
		foundItem = searchIter->second.getPtr();
		va_start(mbrArgs, nBandMembers);
		for (int i = 0; i < nBandMembers; i++) {
			
			charArg = va_arg(mbrArgs, char*);
			mbrArg = string(charArg);
			
			// do something with each keyword
			// 2. add keywords to the non-const item.			
			outputMbrs.insert(mbrArg);
			

			// 3. add the item's title to the keyword index.
			mbrIter = memberIndex.find(mbrArg); // if keyword is already there, add title to keywordINdex
			if (mbrIter != memberIndex.end()) { 
				mbrIter->second.insert(foundItem->getTitle());
			} else { // if keyword isn't already there.
				mbrInsertValue = pair<string, StringSet>(mbrArg, StringSet());
				memberIndex.insert(mbrInsertValue);
				memberIndex.at(mbrArg).insert(foundItem->getTitle());
			}				
		}

		((MusicAlbum*)foundItem)->setBandMembers(outputMbrs);

		va_end(mbrArgs);
	}
}

const ItemSet* Library::musicByBand(const string& band) 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	map<string, StringSet> searchIdx2 = artistIndex;
	return searchIndexTwo(searchIdx1, MusicAlbum::getMediaTypeName(), searchIdx2, band);	
}

const ItemSet* Library::musicByMusician(const string& musician) 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	map<string, StringSet> searchIdx2 = memberIndex;
	return searchIndexTwo(searchIdx1, MusicAlbum::getMediaTypeName(), searchIdx2, musician);
}

const ItemSet* Library::musicAlbums() 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	return searchIndexOne(searchIdx1, MusicAlbum::getMediaTypeName());
}

// movie-related functions

const Item* Library::addMovie(const string& title, const string& director, const int nScenes)
{
	Item* newMovie = new Movie(title, director, nScenes);
	if (itemCollection.count(newMovie->getTitle()) == 0) {
		itemCollection.insert(pair<string, ItemPtr>(title, newMovie));
	} else {
		return 0;
	}

	if (itemCollection.count(newMovie->getTitle()) == 0) {
		return 0;
	} else {
		addMediaIndex(newMovie);
		addArtistIndex(newMovie);

		return newMovie;
	}
}

void Library::addCastMembers(const Item* const movie, const int nCastMembers, ...)
{
// the code in this function demonstrates how to handle a vararg in C++
	va_list					mbrArgs;
	string					mbrArg;
	char*					charMbr; 
	Item*					foundItem; //Item to be looked up from the list.
	string					searchItem = movie->getTitle();
	pair<string, StringSet> mbrInsertValue;
	StringSet				outputMbrs;

	map<string, ItemPtr>::iterator searchIter;
	map<string, StringSet>::iterator mbrIter;
	
	// 1. find the NON-CONST item in the library that matches the search key.
	searchIter = itemCollection.find(movie->getTitle());
	
	if (searchIter != itemCollection.end()) {
		foundItem = searchIter->second.getPtr();
		va_start(mbrArgs, nCastMembers);
		for (int i = 0; i < nCastMembers; i++) {
			charMbr = va_arg(mbrArgs, char*);
			mbrArg = string(charMbr);
			// do something with each keyword
			// 2. add keywords to the non-const item.			
			outputMbrs.insert(mbrArg);

			// 3. add the item's title to the keyword index.
			mbrIter = memberIndex.find(mbrArg); // if keyword is already there, add title to keywordINdex
			if (mbrIter != memberIndex.end()) { 
				mbrIter->second.insert(foundItem->getTitle());
			} else { // if keyword isn't already there.
				mbrInsertValue = pair<string, StringSet>(mbrArg, StringSet());
				memberIndex.insert(mbrInsertValue);
				memberIndex.at(mbrArg).insert(foundItem->getTitle());
			}				
		}

		((Movie*)foundItem)->setCast(outputMbrs);

		va_end(mbrArgs);
	}
}

const ItemSet* Library::moviesByDirector(const string& director) 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	map<string, StringSet> searchIdx2 = artistIndex;
	return searchIndexTwo(searchIdx1, Movie::getMediaTypeName(), searchIdx2, director);
}

const ItemSet* Library::moviesByActor(const string& actor) 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	map<string, StringSet> searchIdx2 = memberIndex;
	return searchIndexTwo(searchIdx1, Movie::getMediaTypeName(), searchIdx2, actor);
}

const ItemSet* Library::movies() 
{
	map<string, StringSet> searchIdx1 = mediaIndex;
	return searchIndexOne(searchIdx1, Movie::getMediaTypeName());
}

//used for dtors?
static void deleteMapContents(StringToItemSetMap& s2ism)
{
	// your code here
}

static void deleteItemSetContents(ItemSet& itemSet)
{
	// your code here
}

//--------------------Private methods:

//TODO: add exception handling?

void Library::copyMap(map<string, StringSet*>*& source, map<string, StringSet*>*& dest) {
	dest->clear();	//clear destination list.
	map<string, StringSet*>::iterator sourceIter;

	dest->insert(source->begin(), source->end());
	return;
}

//Copies item collection... 
void Library::copyItemColl(const Library*& otherLib) {
	this->itemCollection.clear();
	this->itemCollection.insert(otherLib->itemCollection.begin(), otherLib->itemCollection.end());
	return;
}

//copies currentQuery from other library.
void Library::copyCurrentQuery(const Library*& otherLib) {
	this->currentQuery.clear();
	this->currentQuery.insert(otherLib->currentQuery.begin(), otherLib->currentQuery.end());
	return;
}


//not sure about how to deal with this returning an item pointer.. Should I create a "currentQuery" ItemPtr* variable?
//ItemSet* Library::searchIndexOne(map<string, StringSet*>*& searchIndex, string& searchKey) {	

//TODO: trying to insert strings into ItemSet return value, getting hung up in the process.
const ItemSet* Library::searchIndexOne(map<string, StringSet>& searchIndex, const string& searchKey) {	
	ItemSet								retVal;
	map<string, StringSet>::iterator	searchIter;	
	ItemSet::iterator					resultIter;
	StringSet::iterator					idx1Iter;
	StringSet							idx1Set; //set of items matching searchKey (names of Item objects).
	
	currentQuery.clear();
	searchIter = searchIndex.find(searchKey);
	//get set of item names mapped to keyword
	if (searchIter != searchIndex.end()) {
		idx1Set = searchIter->second;
	}

	//get elements of itemCollection corresponding to query result set.
	for (idx1Iter = idx1Set.begin(); idx1Iter != idx1Set.end(); idx1Iter++) {
		currentQuery.insert(itemCollection.at(*idx1Iter));
	}

	return queryPtr;
}

//ItemSet* Library::searchIndexTwo(map<string, StringSet*>*& searchIndexOne, string& searchKeyOne, map<string, StringSet*>*& searchIndexTwo, string& searchKeyTwo) {
const ItemSet* Library::searchIndexTwo(map<string, StringSet>& idx1, const string& searchKeyOne, map<string, StringSet>& idx2, const string& searchKeyTwo) {	
	ItemSet								retVal;
	map<string, StringSet>::iterator	searchIter1;
	map<string, StringSet>::iterator	searchIter2;
	
	//these are to search the result sets of the searchIter searches.
	StringSet::iterator					idx1Iter, idx1IterA, idx1IterB;
	StringSet::iterator					idx2Iter, idx2IterA, idx2IterB;
	
	StringSet							output; //intersect used to be here.
	insert_iterator<StringSet>			outIter(output, output.begin());
	StringSet::iterator					outputIter;
	StringSet::const_iterator					interSect;
	StringSet							idx1Set;
	StringSet							idx2Set;
	
	//clear current search query.
	currentQuery.clear();
	
	//find index entry for current search query.
	searchIter1 = idx1.find(searchKeyOne);
	searchIter2 = idx2.find(searchKeyTwo);

	//Fill first search query
	if (searchIter1 != idx1.end()) {
		idx1Set = searchIter1->second;
	}

	//Fulfill second search query.
	if (searchIter2 != idx2.end()) {
		idx2Set = searchIter2->second;
	}

	//compute set intersection with STL algo
	idx1IterA = idx1Set.begin();
	idx1IterB = idx1Set.end();
	idx2IterA = idx2Set.begin();
	idx2IterB = idx2Set.end();

	set_intersection(idx1Set.begin(), idx1Set.end(), idx2Set.begin(), idx2Set.end(), outIter); 

	//iterate thru set intersection to select the right elements from itemCollection.
	for (outputIter = output.begin(); outputIter != output.end(); outputIter++) {
		currentQuery.insert(itemCollection.at(*outputIter));
	}

	//currentQuery.insert(outPut->begin(), outPut->end());
	//insert set intersection into currentQuery member.
	//currentQuery.insert(outPut->begin(), outPut->end());
	//retVal.insert(outPut->begin(), outPut->end());

	//return currentQuery;
	return queryPtr;
}

void Library::initIndices() {
	//keywordIndex = new map<string, StringSet*>();
	//memberIndex = new map<string, StringSet*>();
	//artistIndex = new map<string, StringSet*>();
	//mediaIndex = new map<string, StringSet*>();
	return;
}


void Library::addLookupIndex(map<string, StringSet>& placeToAdd, const string& itemTitle, StringSet& inputList) {
	StringSet::iterator		inputIter;
	string						currentInput;
	StringSet					newStrSet;
	pair<string, StringSet>	insertValue;

	inputIter = inputList.begin();
	while (inputIter != inputList.end()) {
	//for (inputIter = inputList->begin(); inputIter != inputList->end(); inputIter++) {
		currentInput = *inputIter;
	
		//check if key isn't there and add it if not.
		if (placeToAdd.count(currentInput) == 0) {
			insertValue = pair<string, StringSet>(currentInput, StringSet());
			placeToAdd.insert(insertValue);
		}

		//add the value for the current keyword.
		placeToAdd.at(currentInput).insert(itemTitle);
		inputIter++;
	}
	
	return;
}

void Library::addKeywordIndex(Item*& newItem) {
	StringSet keywdPtr = newItem->getKeywords();
	addLookupIndex(keywordIndex, newItem->getTitle(), keywdPtr);
	return;
}

void Library::addMemberIndex(MusicAlbum*& newAlbum) {
	StringSet mbrPtr = newAlbum->getBandMembers();
	addLookupIndex(memberIndex, newAlbum->getTitle(), mbrPtr);
	return;
}

void Library::addMemberIndex(Movie*& newMovie) {
	StringSet castPtr = newMovie->getCast();
	addLookupIndex(memberIndex, newMovie->getTitle(), castPtr);
	return;
}



void Library::addMediaIndex(Item*& newItem) {
	pair<string, StringSet> insertValue;

	if (mediaIndex.count(newItem->getMediaType()) == 0) { //true if media index doesn't contain item's media type.
		insertValue = pair<string, StringSet>(newItem->getMediaType(), StringSet());
		mediaIndex.insert(insertValue);
	}
	
	//update media index to have 
	mediaIndex.at(newItem->getMediaType()).insert(newItem->getTitle());

	return;
}

void Library::addArtistIndex(Item*& newItem) {
	pair<string, StringSet> insertValue;

	if (artistIndex.count(newItem->getCreator()) == 0) { //true if media index doesn't contain item's media type.
		insertValue = pair<string, StringSet>(newItem->getCreator(), StringSet());
		artistIndex.insert(insertValue);
	}
	
	//update media index to have 
	artistIndex.at(newItem->getCreator()).insert(newItem->getTitle());

	return;
}

//Not putting an AddLibItem method in here because not using reflection for this... relying on class-specific 



bool Library::removeIndices(Item*& outItem) {
	bool removeSuccess = false;
	
	removeSuccess = removeLibraryIndex(artistIndex, outItem);
	removeSuccess = removeLibraryIndex(memberIndex, outItem);
	removeSuccess = removeLibraryIndex(keywordIndex, outItem);
	removeSuccess = removeLibraryIndex(mediaIndex, outItem);
	
	return removeSuccess;	
}

//general index removal method...
bool Library::removeLibraryIndex(map<string, StringSet>& libIndex, Item*& outItem) {
	bool removeSuccess	=				true;
	map<string, StringSet>::iterator	libIndexIter;
	pair<string, StringSet>			eachSet;
	
	for (libIndexIter = libIndex.begin(); libIndexIter != libIndex.end(); libIndexIter++) {
		eachSet = *libIndexIter;
		libIndex.erase(eachSet.first);
	}

	return removeSuccess;

	/*bool								removeSuccess = true;
	map<string, StringSet*>::iterator	libIndexIter;
	StringSet*							eachSet = 0;
		
	for (libIndexIter = libIndex->begin(); libIndexIter != libIndex->end(); libIndexIter++) {
		eachSet = *libIndexIter;		
		libIndex->erase(eachSet);
	}
	
	return removeSuccess;*/
}