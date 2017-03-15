/*
* File:         BitOutputStream.h
* Authors:      Jonathan Chiu, Adrian Cordova
* Class:        CSE 100, Winter 2017
* Date:         2/21/2017
*
* Declaration of BitOutput Stream used for final submission of CSE100.
*/

#include <iostream>
using namespace std;

class BitOutputStream {
  private:
    unsigned char buffer;   // Bitwise buffer (one byte)
    int numBits;            // Number of bits that have been written
    ostream & out;          // Reference to the bytewise output stream

  public:

    /*
     * Constructor function for BitOutputStream.
     */
    BitOutputStream(ostream & os) : out(os), buffer(0), numBits(0) {}

    /*
     * Send the bitwise buffer to the output stream, and clear the
     * bitwise buffer.
     */
    void flush();

    /*
     * Write bit to the bitwise buffer.
     */
    void writeBit(unsigned int bit);

    /*
     * Write a single byte directly to the output stream.
     */
    void writeByte(int byte);

    /*
     * Write a four byte int to the output stream.
     */
     void writeInt(int number);
};
