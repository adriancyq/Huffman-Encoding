/*
* File:         BitOutputStream.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/21/2017
*
* 
*/

#include "BitOutputStream.h"
#include <iostream>
#include <fstream>

using namespace std;
BitOutputStream::~BitOutputStream(){
	if (numbits) flush();
}

void BitOutputStream::writeBit(int x) {
	
	if (out.good()){
		int y = x << (7 - numbits);
		buffer |= y;

		numbits++;

		if (numbits == 8) {
			flush();
		}	
	}
	else {
		flush();
	}
}
