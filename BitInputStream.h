/*
* File:         BitInputStream.h
* Authors:      Jonathan Chiu, Adrian Cordova
* Class:        CSE 100, Winter 2017
* Date:         2/21/2017
*
* Header file for the BitInputStream, for the final submission of PA3.
*/

#include <iostream>
using namespace std;

class BitInputStream {
  private:
    unsigned char buffer;   // Bitwise buffer (one byte)
    int numBits;            // Number of bits that have been read from buffer
    istream & in;           // Reference to the bytewise input stream

  public:

    /*
     * Constructor for the BitInputStream.
     */
    BitInputStream(istream & is) : in(is), buffer(0), numBits(8) {}

    /*
     * Fill the bitwise buffer by reading one byte from the input stream.
     */
    void fill();

    /*
     * Read bit from the bitwise buffer.
     */
    unsigned int readBit();

    /*
     * Read a four-byte int directly from the input stream.
     */
    int readInt();

    /*
     * Read a single byte from the input stream.
     */
    int readByte();
};
