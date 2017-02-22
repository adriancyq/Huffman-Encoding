/*
* File:         BitOutputStream.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/21/2017
*
* Implementation of writeBit and flushing for the BitOutputStream.
*/
#include "BitOutputStream.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Write bit to the bitwise buffer.
 */
void BitOutputStream::writeBit(unsigned int bit) {

	// Bit buffer is full, need to write
	if (numBits == 8) {
		flush();
	}

	// Set the appropriate bit in the buffer
	buffer |= bit << numBits;

	// Increment number of bits
	numBits++;
}

/*
 * Send the bitwise buffer to the output stream, and clear the
 * bitwise buffer.
 */
void BitOutputStream::flush() {

	// Write the bitwise buffer to the ostream and flush
	out.put(buffer);
	out.flush();

	// Reset buffer and number of bits
	buffer = 0;
	numBits = 0;
}
