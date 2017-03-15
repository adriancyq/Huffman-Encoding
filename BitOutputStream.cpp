/*
* File:         BitOutputStream.cpp
* Authors:      Jonathan Chiu, Adrian Cordova
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

/*
 * Write a single byte (8 bits) to the output stream.
 */
void BitOutputStream::writeByte(int byte) {
  out.put(byte);
}

/*
 * Write a four byte integer to the output stream by breaking it up by bytes.
 */
void BitOutputStream::writeInt(int number) {

	// Break the four byte integer to four one-byte pieces
	char part1 = number & 255;
	char part2 = (number >> 8) & (255);
	char part3 = (number >> 16) & (255);
	char part4 = (number >> 24) & (255);

	// Write out each part individually
	out.put(part1);
	out.put(part2);
	out.put(part3);
	out.put(part4);
}
