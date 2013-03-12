#ifndef DISPLAY_H
#define DISPLAY_H

//#include <Windows.h>
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "UDPMessager.h"

class Display
{
public:
	static void printToScreen();
	static void SettingCustomScreenAndBuffer();
};

#endif