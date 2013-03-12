#include <iostream>
#include <fstream>
#include "Person.h"

using namespace std;

char Person::filePath [ENTRY_SZ] = {0};

Person::Person()
{
	Name [0] = 0;
	IP [0] = 0;
	id = 0;
}
Person::Person(char* name, char* ip, int newID)
{
	strcpy_s(Name, ENTRY_SZ, name);
	strcpy_s(IP, ENTRY_SZ, ip);
	id = newID;
}

Person::~Person()
{
}

void Person::setID(int newID) {
	this->id = newID;
}

int Person::getID() {
	return this->id;
}

void Person::setName(char* name) {
	strcpy_s(this->Name, name);
}
void Person::setIP(char* ip)
{
	strcpy_s(IP, ENTRY_SZ, ip);
}
char* Person::getName()
{
	return Name;
}
char* Person::getIP()
{
	return IP;
}
void Person::AppendToFile()
{
	ofstream outData;

	 outData.open(filePath, ios::app);
	
	 outData << Name<<"|"<<IP<<endl; 
	
	 outData.close();
	 outData.clear(std::ios_base::goodbit);
}
void Person::PrintToConsole()
{
	cout <<id<<") " << Name << "   "<<IP<<endl;
}

void Person::ClearListFile()
{
	 ofstream outData;

	 outData.open(Person::filePath);

	 outData.close();
	 outData.clear(std::ios_base::goodbit);
}
