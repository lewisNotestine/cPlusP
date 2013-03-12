                                                                                                                                                                                                                                                      
#include "Display.h"
#include <iostream>
using namespace std;

//using namespace Display;


	void Display::printToScreen()
	{
		int countLines = 0;

		// Declare needed variables
		HANDLE consoleHndl = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screenBuff;
		SetConsoleMode(consoleHndl, ENABLE_QUICK_EDIT_MODE);

		//clear the screen
		system ("cls");

		//set position to 0,0 coordinates for writing oldest message.
		COORD pos0 = {0,0};
		SetConsoleCursorPosition(consoleHndl, pos0);

		int totalMessages = UDPMessager::msgList->GetListLength();
		int startingIndex = 0;
		if (totalMessages > 45)
		{
			startingIndex = totalMessages - 45;
		}
		Node* currentNode =   UDPMessager::msgList->GetFirstNode();
		Msg* currentMessage = (Msg*)currentNode->data;

		int j = 0;
		//traverse to a starting index to make sure only the most recent 45 messages are printed.
		while (j != startingIndex)
		{
			currentNode = currentNode->next;
			currentMessage = (Msg*)currentNode->data;
			j++;
		}
	
		//print most recent 45 entries in the message list
			for (int i = (0 + startingIndex); i < UDPMessager::msgList->GetListLength(); i++)
			{

				string str1 = currentMessage->getName();
				string str2 = currentMessage->getMsg();

				//count the number of lines
				int modDiv = (str1.length() + str2.length() + 2) % 79;
				if (modDiv > 0)
					modDiv = 1;
				else
					modDiv = 0;

				int numLines = (str1.length() + str2.length() + 2) / 79 + modDiv;
				countLines += numLines;

				//currently will wrap at end of 80char line whether in the middle of the word or not
				//later if we feel like implenting it we can use this which will split on spaces only
				//http://cprogramming.com/snippets/source-code/word-wrap-in-c

				cout << str1 << ": " << str2 << endl;

				if (currentNode->next != 0) {
					currentNode = currentNode->next;
					currentMessage = (Msg*)currentNode->data;
				}
			}
	

		/*--------WRITING A LINE OF EQUAL SIGNS TO SEPARATE USER INPUT FROM THE REST OF CONSOLE-----------------*/

		if (countLines < 40)
		{
			COORD pos1 = {0, 40};
			SetConsoleCursorPosition(consoleHndl, pos1);

			cout << "=========================Enter \"xxxx\" to quit===================================" 
				<< "\n\n\n\n";
		}

		if (countLines > 39)
		{
			cout << endl << endl << "=========================Enter \"xxxx\" to quit===================================" 
				<< "\n\n\n\n";
		}
	}

	void Display::SettingCustomScreenAndBuffer()
	{
		//setting screen width and height
		int screenWidthChar = 78;
		int screenHeightChar = 45;
		BOOL result;
		COORD sz = {screenWidthChar + 1, screenHeightChar + 1}; // (width, height)

		// Set the window size and the window buffer
		HANDLE consoleHndl = GetStdHandle(STD_OUTPUT_HANDLE);
		result = SetConsoleScreenBufferSize(consoleHndl, sz);
		SMALL_RECT rect = {0, 0, screenWidthChar, screenHeightChar}; // (left, top, right, bottom)
		result = SetConsoleWindowInfo(consoleHndl, true, &rect);
	}