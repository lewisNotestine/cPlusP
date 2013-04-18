#include <stdlib.h>
#include "BinConverter.h"
#include <iostream>

//Ctors
BinConverter::BinConverter() : 
myOut_(0), 
	myIn_(0),  
	//binOutput_(new std::list<bool>())
	binVector_(new std::vector<bool>())
{}

BinConverter::BinConverter(std::ostream& myOut, std::istream& myIn):
myOut_(&myOut),
	myIn_(&myIn),
	//binOutput_(new std::list<bool>())
	binVector_(new std::vector<bool>())
{}

BinConverter::~BinConverter() {
	/*if (this->binOutput_ != 0) {
		delete this->binOutput_;
		this->binOutput_ = 0;
	}*/

	if (this->binVector_ != 0) {
		delete this->binVector_;
		this->binVector_ = 0;
	}

	if (this->myIn_ != 0) {
		//delete this->myIn_;
		this->myIn_ = 0;
	}

	if (this->myOut_ != 0) {
		//delete this->myOut_;
		this->myOut_ = 0; 
	}
}

/*public methods*/

void BinConverter::test() {
	/*this->binOutput_->push_back(0);
	this->binOutput_->push_back(1);
	this->binOutput_->push_back(0);
	this->binOutput_->push_back(0);
	this->binOutput_->push_back(0);
	this->binOutput_->push_back(1);
	this->binOutput_->push_back(1);*/

	this->clearOutput(sizeof(int) * BYTE);
	this->convertInputToBinary(15);

	this->print();

	
	int intSize = sizeof(int);
	int longSize = sizeof(long);
	int unsSize = sizeof(unsigned int);
	int unlongSize = sizeof(unsigned long);

}

void BinConverter::convertToBinary(const int& input) {

}

void BinConverter::convertToBinary(const char*& input) {

}

void BinConverter::print() {
	for (int i = binVector_->size() - 1; i >= 0; i--) {
		*myOut_ << binVector_->at(i);
	}
}

void BinConverter::setIstream(std::istream& myIn) {

}

void BinConverter::setOstream(std::ostream& myOut) {

}

std::istream* BinConverter::getIstream() {
	return (this->myIn_);
}

std::ostream* BinConverter::getOstream() {
	return (this->myOut_);
}


/*private methods*/

void BinConverter::convertInputToBinary(const int& input) {	
	
	//find maximum power of two from input, by taking log and truncating to int. 
	double floatlog = log((double)input)/log((double)BinConverter::BASETWO);
	int maxLog = static_cast<int>(floatlog);
	int remainder = input - (int) pow((float)BASETWO, maxLog);
	
	//handle signed/unsigned dichotomy with two's complement...


	//assert(remainder >= 0); //less than zero is no good
	//set the power of two of the output array at maxlog to be equal to 1.
	this->binVector_->at(maxLog) = 1;

	if (remainder > 0) {
		//recursively apply the algorithm
		this->convertInputToBinary(remainder);
	} else {
		//fill out remaining zeroes in the vector.

	}

}

void BinConverter::convertInputToBinary(const char*& input) {

}

void BinConverter::clearOutput() {
	binVector_->clear();
}	

void BinConverter::clearOutput(const int& newSize) {
	binVector_->clear();
	binVector_->resize(newSize, 0);
	
	return;
}