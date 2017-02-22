/*
* File:         uncompress.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/15/2017
*
* Given an encoded file, decode it with a Huffman encoding tree. The encoded
* file will have a file header, where the first 256 lines represent the
* frequency of character i.
*/
#include <iostream>
#include <fstream>
#include "HCTree.h"
#include "HCNode.h"


using namespace std;
int main(int argc, char* argv[])
{

  // Check that user supplied filenames
  if (argc < 3) {
    cerr << "Pass in the input and output files." << endl;
    return -1;
  }

  ifstream inputFile;                   // Input stream
  int next;                             // Next char in the input stream
  int totalBytes = 0;                   // Total number of chars to be decoded
  int totalUniqueSymbols = 0;           // Total number of unique symbols
  vector<int> freqs(256, 0);            // Count of each char found

  // Open input filestream
  string inputFileName = argv[1];
  inputFile.open(inputFileName, ios::binary);

  // Reconstruct the freqs vector to reconstruct the Huffman tree
  cout << "Reading header from file \"" << inputFileName << "\"... ";
  for (int i = 0; i < 256; i++) {
    inputFile >> next;
    freqs[i] = next;

    // Found an occurring char to decode
    if (next > 0) {
      totalBytes += next;
      totalUniqueSymbols++;
      cerr << "Character " << i << ": " << next << endl;
    }
  }

  // INFO: Print stats on input file
  cout << "done." << endl;
  cout << "Uncompressed file will have " << totalUniqueSymbols
        << " unique symbols and size " << totalBytes << " bytes." << endl;

  // Reconstruct the Huffman tree
  cout << "Building Huffman code tree... ";
  HCTree huffman;
  huffman.build(freqs);
  cout << "done." << endl;

  // Open the output file for writing
  ofstream outputFile;                  // Output stream
  string outputFileName = argv[2];      // Name of output file
  cout << "Writing to file \"" << outputFileName << "\"... ";
  outputFile.open(outputFileName, ios::binary);
  BitInputStream bistream(inputFile);

  // FIXME Gets the last newline character after the 256th frequency
  inputFile.get();
  
  // Read all expected bytes
  for (int i = 0; i < totalBytes; i++) {
    if (inputFile.eof()) { break; }

    // Decode and write to output
    outputFile << (unsigned char) huffman.decode(bistream);
  }

  // Close input and output streams
  cout << "done." << endl;
  inputFile.close();
  outputFile.close();
  return 0;
}
