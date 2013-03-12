#pragma once

#include "item.h"

class MusicAlbum :
	public Item
{
private:
	static const string MEDIA_TYPE;
	static const string DIV_TYPE;
	static const string CREATOR_TYPE;
	static const string MEMBERS;

	set<string> bandMembers;

	void initMbrs();
	string printMbrs() const;

	
public:
	static string getMediaTypeName();

	MusicAlbum(void);
	MusicAlbum(const string& newTitle);
	MusicAlbum(const string& newTitle, const string& newCreator, const int& newDivs);
	~MusicAlbum(void);
	//This never actually got used in the final version...
	//string getMediaType()

	//late binding functs
	string toString() const;	
	string getMediaType() const;
	string getDivType() const;
	string getCreatorType() const;
	//early-bind funct.
	string getMbrType() const;

	string getBand() const;
	bool hasBandMember(const string& qryMbr) const;
	set<string> getBandMembers() const;

	void setBand(const string& newBand);
	void addBandMembers(const int& nArgs, ...);	
	void setBandMembers(const set<string>& bandMbrs);
};

