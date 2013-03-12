/*
Authors:		Chad Johnson, Lewis Notestine, Noah Senitz
				CS162 Spring 2012 - Instructor: G. Gross, 
				
Assignment:		5 

Date:			6/4/2012

Sources:		On using the C time libraries to time-stamp messages:
					http://www.cplusplus.com/reference/clibrary/ctime/
				On formatting word wrap.
					http://cprogramming.com/snippets/source-code/word-wrap-in-c

Description:	Uses UDP to implement an IM application on a LAN.  Users can start IMs and manage contact library.
				Messages are logged to file (in same location as contacts library). When in IM, users can enter 'xxxx' to quit.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "LinkedList.h"
#include "SocketUDPComm.h"
#include "UDPMessager.h"
#include "Person.h"
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include "Display.h"

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

using namespace std;

enum menuChoice { SENDNEW, PRINT, ADDCONT, DELCONT,  QUIT };


void	displayMenu();
void	getMenuInput(menuChoice& inChoice);
void	executeChoice(const menuChoice& inChoice, LinkedList*& personList);
void	addPersonByInput(LinkedList*& personList);
char*	pickPersonToDelete();
void	deletePerson(char* personTitle, LinkedList*& personList);
void	openFile(LinkedList*& personList);
void	buildList(ifstream& inFile, LinkedList*& personList);
void	clearList(LinkedList*& personList);
void	printContacts(LinkedList* personList);
void	writeListToFile(LinkedList*& personList);
Person* pickPersonToIM(LinkedList*& personList);
void	sendMessages(Person* chatPrtnr, LinkedList*& messageList);
bool	startConversation(Person* chatPrtnr);
void	setMsgFilePath(Person* chatter);
void	writeMsgsToFile() ;


int main() {
	menuChoice 		userChoice;
	LinkedList*		personList = 0; //List of contacts.
	openFile(personList);		//populate the list on opening the program.

	do {
		displayMenu();
		getMenuInput(userChoice);
		executeChoice(userChoice, personList);
	} while (userChoice != QUIT);

	_CrtDumpMemoryLeaks();

	return 0;
}

void displayMenu() {
	cout << endl << "Please enter your choice:" << endl;
	cout << "a) Choose contact and start an IM!" << endl
			<< "b) Print contacts" << endl
			<< "c) Add contact" << endl
			<< "d) Delete contact" << endl
			<< "e) Quit" << endl;
	return;
}

//
void getMenuInput(menuChoice& inChoice) {
	string 	userInput;
	char 	charInput;

	do {
		getline(cin, userInput);  //Use getline to keep buffer in order, convert to c-str after input.
		charInput = tolower(userInput.c_str()[0]);
		if (charInput == 'a') {
			inChoice = SENDNEW;
		} else if (charInput == 'b') {
			inChoice = PRINT;
		} else if (charInput == 'c') {
			inChoice = ADDCONT;
		} else if (charInput == 'd') {
			inChoice = DELCONT;
		} else if (charInput == 'e') {
			inChoice = QUIT;
		} else {
			cout << "invalid menu choice." << endl;
		}
	} while (!(charInput == 'a' || charInput == 'b' || charInput == 'c' || charInput == 'd' || charInput == 'e'));

	return;
}

void executeChoice(const menuChoice& inChoice, LinkedList*& personList) {

	char		personToDelete[ENTRY_SZ];
	bool		channelIsOpen = false;
	Person*		personToUse = 0;

	if (inChoice == SENDNEW) {
		//1. Pick the contact to send a message.
		personToUse = pickPersonToIM(personList);

		//2. send a message to that contact.
		channelIsOpen = startConversation(personToUse);
		if (channelIsOpen) {
			UDPMessager::msgList = new LinkedList; // initialize the LinkedList.
			//3. Start listening for messages from contact, print when they show up. 
			//this is where we send incoming & outgoing messages to display.
			sendMessages(personToUse, UDPMessager::msgList);
		}
	} else if (inChoice == PRINT) { 		//Print the contacts
		printContacts(personList);
	} else if (inChoice == ADDCONT) { 		//add to contacts. 
		addPersonByInput(personList);
	} else if (inChoice == DELCONT) {
		strcpy_s(personToDelete, pickPersonToDelete());
		deletePerson(personToDelete, personList);
	} else if (inChoice == QUIT) {
		clearList(personList);	
	}
	return;
}

/*-----FUNCTIONS TO MANAGE MESSAGING SESSIONS-----------*/

bool startConversation(Person* chatPrtnr) {
	Display::SettingCustomScreenAndBuffer();
	bool msgStatus;
	msgStatus = (UDPMessager::StartTwoWayComm(chatPrtnr) == 0); //This starts the 2way comm and returns 0 if it's working.
	
	return msgStatus;
}

//starts the chain of messages.
void sendMessages(Person* chatPrtnr, LinkedList*& messageList) {
	Msg*	currentMsg = 0;
	string	inputMsg;
	bool	quitMsgs = false;
	string	quitFlag = "xxxx";	//user enters this sequence to quit.
	char	charMsg[ENTRY_SZ], outgoingName[ENTRY_SZ] = "ME" ;
	int		msgCnt = 0;
	
	//Set file path for stored msgs.
	setMsgFilePath(chatPrtnr);

	do {
		//get user input for message - TODO: may call display controller?
		getline(cin, inputMsg); 
		strcpy_s(charMsg, inputMsg.c_str());

		currentMsg = new Msg(charMsg, outgoingName, msgCnt);		//create message object.
		messageList->AddLinkToBack(currentMsg);						//add message to linkedList
		Display::printToScreen();									//Call display print new msg.;
		UDPMessager::SendMessage(currentMsg ,chatPrtnr);			//send the message using UDPMessager.

		//quit after we sent the message. 
		if (inputMsg == quitFlag) {
			quitMsgs = true;
		}

	} while (!quitMsgs);

	//close UDP messager after comm ends. 
	UDPMessager::EndTwoWayComm();

	//write msg list to file.
	writeMsgsToFile();

	//exit application with non-error.
	cout << "Thank you for using the chat application.  Press a key to quit." << endl;
	system("pause");
	exit(0);

	return;
}

/*-----FUNCTIONS TO MANAGE PERSON LIST-------------*/

//Add a person by console input.
void addPersonByInput(LinkedList*& personList) {
	string	curtPath, curtIP;
	char	charPath[ENTRY_SZ], charIP[ENTRY_SZ];
	Person*	newPerson = 0;

	if (personList != 0) {
		cout << "Input contact name: ";
		getline(cin, curtPath); 
		cout << "input contact IP address: ";
		getline(cin, curtIP);

		strcpy_s(charPath, curtPath.c_str());
		strcpy_s(charIP, curtIP.c_str());
		newPerson = new Person(charPath, charIP, personList->GetListLength());
		newPerson->AppendToFile();
		personList->AddLinkToBack((void*)newPerson);

	} else {
		cout << "No list loaded!" << endl;
	}
	return;
}

Person* pickPersonToIM(LinkedList*& personList) {
	Person*	personToIM = 0;
	string		idToUse;
	char*		charID;
	Node*		curtNode = 0;
	Person*		curtPerson = 0;
	
	cout << "Pick a contact to send a message! " << endl;
	
	//display persons to IM.
	curtNode = personList->GetFirstNode();
	
	for (int i = 0; i < personList->GetListLength(); i++) {
		curtPerson = (Person*)curtNode->data;
		cout << curtPerson->getID() << ") " <<
			curtPerson->getIP() << " " << curtPerson->getName() << endl;
		curtNode = curtNode->next;
	}

	//user makes the choice.
	getline(cin, idToUse);
	charID = &idToUse.at(0);
	
	//find person in list, assign to return val.
	curtNode = personList->GetFirstNode();
	for (int i = 0; i < personList->GetListLength(); i++) {
		curtPerson = (Person*)curtNode->data;
		if (atoi(charID) == curtPerson->getID()) {
			personToIM = curtPerson;
			break;
		} else if (i == personList->GetListLength() - 1) {
			cout << "Person not found!" << endl;
			break;
		}
		curtNode = curtNode->next;
	} 

	return personToIM;
}

char* pickPersonToDelete() {
	string	persName;
	char	charName[ENTRY_SZ];

	cout << "Choose contact to delete: ";
	getline(cin, persName);
	strcpy_s(charName, persName.c_str());

	return charName;
}

//Delete the appropriate person.  
void deletePerson(char* Name, LinkedList*& personList) {
	Node*	ptr = 0;
	void*	deleteNode;
	void*	curtPtr = 0;
	Person*	curtPers = 0;
	bool	personMatch = false;
	Name;
	
	ptr = personList->GetFirstNode();

	for (int i = 0; i < (personList->GetListLength()); i++)
	{
		Person* ptr1 = (Person*) ptr->data;
		if (!strcmpi(Name, ptr1->getName()))
		{
			personMatch = true;
			break;
		}
		ptr = ptr ->next;
	}

	if (personList != 0 && personMatch == true) {
		//do stuff to delete the person.
		deleteNode = personList->RemoveThisLink(ptr);
		Person* curtPers = (Person*) deleteNode;		
		curtPers->ClearListFile();
		delete curtPers;
		ptr = personList->GetFirstNode();	
		
		for (int i = 0; i<personList->GetListLength(); i++)
		{
			curtPers = (Person*) ptr->data;
			curtPers->AppendToFile();
			ptr = ptr->next;
		}

	} else {
		cout << "No person list loaded!";
	}

	return;
}

void openFile(LinkedList*& personList) {
	ifstream	inFile;
	string		strPath;
	
	do {
		cout << endl << "Enter the full file path of contacts file: ";
		getline(cin, strPath);
		strcpy_s(Person::filePath, strPath.c_str());
		inFile.open(Person::filePath);
		if (!inFile.is_open()) {
			cout << endl << "Not a valid filename.";
		}
	} while(!inFile.is_open());
	assert(inFile.is_open());

	//do stuff to populate the linked list. 
	buildList(inFile, personList);

	//reset, close inFile.
	inFile.ignore(256, '\n');
	inFile.close();
	inFile.clear(std::ios_base::goodbit);

	cout << endl << personList->GetListLength() << 
		" contacts loaded from file \'" << Person::filePath << "\'"<< endl;
	return;
}

//takes open ifstream and reads objects to linked list.
void buildList(ifstream& inFile, LinkedList*& personList) {
	string	nameInput, ipInput;
	char	charName[ENTRY_SZ], charIP[ENTRY_SZ];
	char	delim = '\|';
	int		idCnt = 0; // used to populate person.id field.

	personList = new LinkedList;
	
	//use getline to parse comma-delimited text file. 
	while (!inFile.eof()) {

		//first get the name and create the person object.
		getline(inFile, nameInput, delim);
		if (nameInput != "") {
			strcpy_s(charName, nameInput.c_str());
		} else {
			break;
		}

		getline(inFile, ipInput);
		if (ipInput != "") {
			strcpy_s(charIP, ipInput.c_str());
		} else {
			break;
		}
			
		Person* newPerson = new Person(charName, charIP, idCnt);
		newPerson->setID(idCnt);

		//Next, add person object to personList.
		personList->AddLinkToBack(newPerson);
		
		idCnt++;
	}

	UDPMessager::CopyPersonList(personList);

	inFile.ignore(256,'\n');
	inFile.clear(std::ios_base::goodbit);
	inFile.close();

	return;
}

//to clear list if already implemented.
void clearList(LinkedList*& personList) {
	if (personList != 0) {
		void*	curtPtr = 0;
		long	len = personList->GetListLength();

		if (len > 0) {
			//1. delete each person in list.
			for (int i = 0; i < len; i++) {
				curtPtr = personList->RemoveLinkFromFront();
				cout << "Deleting person at index: " << i << endl;
				//cast data as person, delete.
				delete (Person*)curtPtr;
				curtPtr = 0;
			}

			//2. delete list itself.
			if (personList != 0) {
				delete personList;
				personList = 0;
			}
		}
	}
	return;
}

//Print all persons in list.
void printContacts(LinkedList* personList) {
	Node* curtNode = 0;
	Person* curtPerson = 0;

	if (personList->GetListLength() > 0) {
		curtNode = personList->GetFirstNode();
		for (int i = 0; i < personList->GetListLength(); i++) {
			curtPerson = (Person*)curtNode->data;
			curtPerson->PrintToConsole();
			curtNode = curtNode->next;
		}
	}
	return;
}

//takes list and rewrites to file.
void writeListToFile(LinkedList*& personList) {
	ofstream	outFile;
	Node*		curtNode = 0;
	Person*		curtPerson = 0;

	//1. open file.  
	outFile.open(Person::filePath);
	assert(outFile.is_open());

	curtNode = personList->GetFirstNode();
	//2. add each member of current list to file.
	for (int i = 0; i < personList->GetListLength(); i++) {
		curtPerson = (Person*)curtNode->data;
		outFile << curtPerson->getName() << curtPerson->getIP() << endl;
		curtNode = curtNode->next;
	}

	//3. output file, overwriting current personList.txt or whatever.
	outFile.close();
	outFile.clear(std::ios_base::goodbit);

	return;
}

void setMsgFilePath(Person* chatter) {
	char delim = '\\';
	char buff[ENTRY_SZ];
	time_t now = time(0);
	struct tm * timeinfo;
	
	if (Person::filePath != "") {
		string strPath = Person::filePath;
		//parse filepath to get directory of contacts list.
		strPath = strPath.substr(0, strPath.find_last_of(delim));
		//add current date time to message.
		time(&now);
		timeinfo = localtime(&now);
		strftime( buff, ENTRY_SZ, "%I%M%p.txt", timeinfo);
		strPath += ("\\" + string(chatter->getName()) + string(buff) );
		strcpy_s(Msg::filePath, strPath.c_str());
	}
	return;
}

void writeMsgsToFile() {
	ofstream	outFile;
	Node*		curtNode = 0;
	Msg*		curtMsg = 0;

	//1. open file.  
	outFile.open(Msg::filePath);
	assert(outFile.is_open());

	curtNode = UDPMessager::msgList->GetFirstNode();
	//2. add each member of current list to file.
	for (int i = 0; i < UDPMessager::msgList->GetListLength(); i++) {
		curtMsg = (Msg*)curtNode->data;
		outFile << curtMsg->getName() << " " << curtMsg->getMsg()  << endl;
		curtNode = curtNode->next;
	}

	//3. output file
	outFile.close();
	outFile.clear(std::ios_base::goodbit);

	return;

}