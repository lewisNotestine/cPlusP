#ifndef BINCONVERTER_H
#define BINCONVERTER_H

#include <stdlib.h>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>


/*Class BinConverter: takes integer or char input 
and outputs a binary representation of that number using given input/output streams.
*/
class BinConverter {
	//Data members
	std::vector<bool>* binVector_;
	//std::list<bool>* binOutput_;
	std::ostream* myOut_;	//channel for input-output of class.
	std::istream* myIn_;
	const static int BASETWO = 2;
	const static int BYTE = 8;	//bits per byte.


public:
	//ctors
	BinConverter();
	BinConverter(std::ostream& myOut, std::istream& myIn);
	BinConverter(const BinConverter& otherConverter);	// copy ctor.
	~BinConverter();

	//tests 
	void test();

	//public methods
	void convertToBinary(const int& input);
	void convertToBinary(const char*& input);	//
	void print();								//prints the current state of the binary output.

	void setIstream(std::istream& myIn);
	void setOstream(std::ostream& myOut);
	std::istream* getIstream();
	std::ostream* getOstream();


private:
	//Converts the input to a string-formatted binary representation and return the value to the public client method.
	void convertInputToBinary(const int& input);
	void convertInputTOBinary(const char& input);
	void convertInputToBinary(const char*& input);	//for a string.
	void convertInputToBinary(const unsigned int& input);
	void convertInputToBinary(const unsigned char& input);
	void convertInputToBinary(const unsigned char*& input);	//for a string.
	void clearOutput();	//clears the output array.
	void clearOutput(const int& newSize);	//clears the output array and resets it to the length given in the parameter.
};

#endif