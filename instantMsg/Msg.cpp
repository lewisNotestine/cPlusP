#ifndef MSG_H 
#define MSH_H

#include "Msg.h"
#include <iostream>
#include <fstream>

using namespace std;

char Msg::filePath [ENTRY_SZ] = {0};

Msg::Msg()
{
	userName [0] = 0;
	msg [0] = 0;
}

Msg::Msg(char* message, char* name, int id) {
	strcpy_s(msg, message);
	strcpy_s(userName, name);
	ID = id;
}

Msg::Msg(const Msg* newMsg) {

}
Msg::~Msg()
{

}
void Msg::setName(char* newName) 
{
	strcpy_s(userName, ENTRY_SZ, newName);
}

void Msg::setMsg(char* message)
{
	strcpy_s(msg, ENTRY_SZ, message);
}

char* Msg::getName() {
	return this->userName;
}  

char* Msg::getMsg() {
	return this->msg;
}
	
void Msg::AppendToFile() 
{
	 ofstream outData;

	 outData.open(filePath, ios::app);
	
	 outData << userName<<":"<<msg <<endl; 
	
	 outData.close();
	 outData.clear(std::ios_base::goodbit);
}

#endif
