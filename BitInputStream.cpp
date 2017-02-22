#include <iostream>
#include "BitInputStream.h"

using namespace std;

void BitInputStream::fill() {

  // Get a single byte from the input stream
  buffer = in.get();
  numBits = 0;

}

unsigned int BitInputStream::readbit() {

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
