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
  //int next;                             // Next char in the input stream
  vector<int> freqs(256, 0);            // Count of each char found

  // Open input filestream
  string inputFileName = argv[1];
  inputFile.open(inputFileName, ios::binary);

  int n; //change
  byte buffer;
  int total = 0; 
  // Reconstruct the freqs vector to reconstruct the Huffman tree
  for (int i = 0; i < freqs.size(); i++) {
    inputFile >> n;
    if (!inputFile.good()){
      cout << "Error reading file header." << endl;
      cout << "please check \"" << inputFileName << "\" was compressed properly and try again." << endl;
      inputFile.close();
    } 
    freqs[i] = n;
    total += n;
  }

  // Reconstruct the Huffman tree
  HCTree huffman;
  huffman.build(freqs);

  // Open the output file for writing
  ofstream outputFile;                  // Output stream
  string outputFileName = argv[2];      // Name of output file
  outputFile.open(outputFileName, ios::binary);
  //change
  if (outputFile.fail()) {
    cout << "Error: failed to open output stream!" << endl;
    cout << "please check write permissions and try again." << endl;
    return -1;
  }

  BitInputStream bistream(inputFile);

  //change
  for (int i =0; i < total; i++){
    buffer = huffman.decode(bistream);
    if (buffer == (byte)-1) break;
    outputFile.put(buffer);
  }

  // Close input and output streams
  inputFile.close();
  outputFile.close();
  return 0;
}
