#ifndef UDPMESSAGER_H
#define UDPMESSAGER_H

#include "SocketUDPComm.h"
#include "Msg.h"
#include "Person.h"
#include "LinkedList.h"
#include "Display.h"

class UDPMessager {
private:
	static int				UDPPort;
	static CSocketUDPComm	UDPLink;
	static bool				twoWayCommOpen; //indicates whether the twoWayComm is open. 
	static void				ReceiveMessage(const char* inMessage, const char* IP);		//Callback funct, sets currentMsg member a message object from incoming data and returns it.

public:
	static void CopyPersonList(LinkedList* psnAddress);
	static LinkedList* msgList;
	static LinkedList* psnList;
	static int StartTwoWayComm(Person* psnToContact);				//opens thread to receive messages. called by starting and by sendMessage.
	static void SendMessage(Msg* msgToSend, Person* psnContact);	//Sends a message to a remote host.
	static Msg* OutputMsg();										//outputs the current message to caller.
	static void RemoveMsg(Msg* msgToRemove);
	static void EndTwoWayComm();
 };

#endif
