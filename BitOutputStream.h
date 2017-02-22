/*
* File:         BitOutputStream.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/21/2017
*
* 
*/

#define BOSTREAM_HPP
#include <fstream>
using namespace std;

class BitOutputStream {
    private:
        unsigned char buffer; // bitwise buffer (one byte)
        int numbits;         // number of bits that have been written to the 
        ostream & out;     // reference to the bytewise output stream (a C++ ostream)

    public:
        // constructor: assign 'out' to 'os', 'buffer' to 0, and 'numbits' to 0
        BitOutputStream(ostream & os) : out(os), buffer(0), numbits(0) {}

        // send the bitwise buffer to the output stream, and clear the bitwise buffer
        void flush() {
            out.put(buffer);  // write the bitwise buffer to the ostream
            out.flush();   // flush the ostream (optional, slower to do it here)
            buffer = 0;       // clear the bitwise buffer
            numbits = 0;     // bitwise buffer is cleared, so there are 0 bits in it
        }

        // write bit to the bitwise buffer
        void writeBit(unsigned int bit);
};