/*
References:
base-changing algorithm:
	http://en.wikipedia.org/wiki/Logarithm#Change_of_base
*/
#include <stdlib.h>
#include <iostream>
#include "BinConverter.h"

using namespace std;



int main() {
	BinConverter myBinConvert(std::cout, std::cin);
	myBinConvert.test();

	return 0;
}