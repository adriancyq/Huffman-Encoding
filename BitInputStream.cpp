#include <iostream>
#include "BitInputStream.h"

using namespace std;

void BitInputStream::fill() {

  // Get a single byte from the input stream
  buffer = in.get();
  numBits = 0;

}

unsigned int BitInputStream::readBit() {

  // All the bits in the buffer have been read, get new bits
  if (numBits == 8) {
    fill();
  }

  // Get the next bit using a mask
  unsigned int nextBit = buffer & (1 << numBits);

  // Increment the number of bits we have read
  numBits++;

  // If it's greater than 0, the bit of interest is a 1
  if (nextBit > 0) { return 1; }

  // Bit of interest is 0
  else { return 0; }
}

/*
 * Read a four-byte int directly from the input stream.
 */
int BitInputStream::readByte() {
  return in.get();
}

/*
 * Read a single byte from the input stream.
 */
int BitInputStream::readInt() {

  // Get all four bytes of the four-byte int
  int part1 = in.get();
  int part2 = in.get();
  int part3 = in.get();
  int part4 = in.get();

  // Assemble the int back together
  int result = part1;
  result |= (part2 << 8);
  result |= (part3 << 16);
  result |= (part4 << 24);
  return result;
}
