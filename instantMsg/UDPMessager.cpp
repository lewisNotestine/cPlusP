//TODO: DO we even need this class?
#include "UDPMessager.h"
#include <iostream>


using namespace std;

//using namespace Display;

const int IPADDR_BUFFER_SIZE = 16;
const int SEND_BUFFER_SIZE = 1024;

//static data mbrs.
int				UDPMessager::UDPPort = 55551; 
CSocketUDPComm	UDPMessager::UDPLink;
bool			UDPMessager::twoWayCommOpen;
LinkedList*		UDPMessager::msgList;
LinkedList*		UDPMessager::psnList;

void UDPMessager::CopyPersonList(LinkedList* psnAddress)
{
	psnList = psnAddress;
}
//Static functs.
int UDPMessager::StartTwoWayComm(Person* psnContact)
{
    char ipAddr[IPADDR_BUFFER_SIZE];
    
    int retVal = 0;

    try
    {
        // use IP address from the contact used...
        strcpy_s(ipAddr, psnContact->getIP());

        // Before sending anything, start a listening thread so can see what
        // the remote user is saying.
		UDPMessager::UDPLink.StartListenerThread(UDPMessager::UDPPort, UDPMessager::ReceiveMessage);

        // Now let the custom socket class start the loop that allows the
        // user to send text to the remote system through the console and
        // read text sent from the remote user.
        if (UDPMessager::UDPLink.InitializeSenderSocket(ipAddr, UDPMessager::UDPPort) != 0)
        {
            // Can't work without this so bypass loop
            throw;
        }
    }
    catch (...)
    {
        UDPMessager::UDPLink.SetTerminateNow(true);
        cout << "Error!" << endl;
        retVal = -1;
    }

	if (retVal != -1) {
		UDPMessager::twoWayCommOpen = true;
	}

    return retVal;
}

//Callback function, called when listener receives packet.
void UDPMessager::ReceiveMessage(const char* inMessage, const char* IP) {
	Msg*	newMsg = 0;
	int		newID = UDPMessager::msgList->GetListLength();
	char	charMsg[ENTRY_SZ];
	char	charIP[ENTRY_SZ];
	char	curtName[ENTRY_SZ];
	char	curtIP[ENTRY_SZ];

	strcpy_s(charMsg, inMessage);
	strcpy_s(charIP, IP);
	

	//call the display class. if not a quit message, display.  Else, close port.
	//if (string(charMsg) != "xxxx" ) {

	//search the person class for a matching name to the IP
	Node* curtNode = 0;
	Person* curtPerson = 0;
	strcpy(curtName, charIP);

	if (psnList->GetListLength() > 0) {
		curtNode = psnList->GetFirstNode();
		for (int i = 0; i < psnList->GetListLength(); i++) {
			curtPerson = (Person*)curtNode->data;
			strcpy(curtIP, curtPerson->getIP());
			
			if(strcmpi(charIP, curtIP) ==0)
			{
				strcpy(curtName, curtPerson->getName());
				break;
			}
			curtNode = curtNode->next;
		}
	}
		newMsg = new Msg(charMsg, curtName, newID);
		UDPMessager::msgList->AddLinkToBack(newMsg);
	//} else {
	//	newMsg = new Msg("Your partner has left the chat.  Type 'xxxx' to exit.", charIP, newID);
	//	UDPMessager::msgList->AddLinkToBack(newMsg);
	//	UDPMessager::EndTwoWayComm();
	//}

	Display::printToScreen();

	return;
}

void UDPMessager::SendMessage(Msg* msgToSend, Person* psnContact) { 
	char	sendBuff[SEND_BUFFER_SIZE];
	string	strMsg;

	if (UDPMessager::twoWayCommOpen) {
		UDPMessager::UDPLink.SendData(msgToSend->getMsg());
    }
	return;
}

void UDPMessager::EndTwoWayComm() {
	if (UDPMessager::twoWayCommOpen == true) {
		UDPMessager::UDPLink.SetTerminateNow(true);
		UDPMessager::twoWayCommOpen = false;
	}
	return;
}