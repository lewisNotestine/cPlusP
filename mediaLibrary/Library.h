// do not remove any of the function prototypes from this class definition

#pragma once

#include <map>
#include <set>
#include <string>
#include "Item.h"
#include "Movie.h"
#include "MusicAlbum.h"
#include "Book.h"
#include <iterator>

using namespace std;

// C++ Standard Library definitions for containers you may need
typedef set<string>				StringSet;
typedef set<ItemPtr>			ItemSet;				// see comment in Item.h about use of ItemPtr
typedef map<string,ItemSet*>	StringToItemSetMap;

class Library
{
private:
	// put string indices here. 
	//StringToItemSetMap		keywordIndex;
	//StringToItemSetMap		artistIndex;
	//StringToItemSetMap		memberIndex;
	//StringToItemSetMap		mediaIndex;

	//TODO: should each of these indices be pointers? 
	map<string, StringSet>	keywordIndex;
	map<string, StringSet>	artistIndex;
	map<string, StringSet>	memberIndex;
	map<string, StringSet>	mediaIndex;
	map<string, ItemPtr>	itemCollection;
	ItemSet					currentQuery;
	const ItemSet*				queryPtr;		//stores the current query being executed by the selection query methods.  
	//TODO: Consider using const-iterators or iterators to store searches instead of ItemSet?

	const ItemSet* searchIndexOne(map<string, StringSet>& searchIndex, const string& searchKey) ;
	const ItemSet* searchIndexTwo(map<string, StringSet>& searchIndexOne, const string& searchKeyOne, map<string, StringSet>& searchIndexTwo, const string& searchKeyTwo) ;

	//void searchIndexOne(map<string, StringSet*>*& searchIndex, string& searchKey) ;
	//void searchIndexTwo(map<string, StringSet*>*& searchIndexOne, string& searchKeyOne, map<string, StringSet*>*& searchIndexTwo, string& searchKeyTwo) ;

	//Copies any of the collections to the destination index, used in copy ctor.
	void copyMap(map<string, StringSet*>*& source, map<string, StringSet*>*& dest);
	void copyItemColl(const Library*& otherLib);
	void copyCurrentQuery(const Library*& otherLib);

	void initIndices(); //initializes indices.
	void addLookupIndex(map<string, StringSet>& placeToAdd, const string& itemTitle, StringSet& inputList); 
	void addKeywordIndex(Item*& newItem);
	void addMemberIndex(MusicAlbum*& newAlbum);
	void addMemberIndex(Movie*& newMovie);
	void addMediaIndex(Item*& newItem);
	void addArtistIndex(Item*& newItem);

	//TODO: This used Java reflection in Asgmt03.  May have to do differently in C++.
	Item* addLibItem(const string& title, const string& author, const int& nPages, const int& nArgs, ...);
	bool removeLibItem(const string& title); //removes an item from the library.
	bool removeIndices(Item*& outItem);		//removes all indices from an item deleted from library.
	bool removeLibraryIndex(map<string, StringSet>& libIndex, Item*& outItem);	//removes a single item from a single index; called by function above.




public:
	//test function.
	void testIndices(StringSet& testStrSet); 
	// Ctor/dtor.

	Library(); 
	Library(const Library*& otherLib);
	// virtual dtor so subclass pointer objects can call their own dtor... 
	virtual ~Library();

	// general functions
	void addKeywordsForItem(const Item* const item, int nKeywords, ...);
	void testItemsForKeyword(string parameter);	
	const ItemSet* itemsForKeyword(const string& keyword);
	Library clone(); //returns a deep copy of the current library.

	// book-related functions
	const Item* addBook(const string& title, const string& author, const int nPages);
	const ItemSet* booksByAuthor(const string& author) ;
	const ItemSet* books() ;			// returns set containing all the books

	// music-related functions
	const Item* addMusicAlbum(const string& title, const string& band, const int nSongs);
	void addBandMembers(const Item* const musicCD, int nBandMembers, ...);
	const ItemSet* musicByBand(const string& band) ;
	const ItemSet* musicByMusician(const string& musician) ;
	const ItemSet* musicAlbums() ;		// returns set containing all the music

	// movie-related functions
	const Item* addMovie(const string& title, const string& director, const int nScenes);
	void addCastMembers(const Item* const movie, const int nCastMembers, ...);
	const ItemSet* moviesByDirector(const string& director) ;
	const ItemSet* moviesByActor(const string& actor) ;
	const ItemSet* movies() ;			// returns set containing all the movies	
};