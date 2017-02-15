#include <iostream>
#include <fstream>
#include "HCTree.h"
#include "HCNode.h"

int main(int argc, char* argv[])
{

  // Check that user supplied filenames
  if (argc < 3) {
    cerr << "Pass in the input and output files." << endl;
    return -1;
  }

  ifstream inputFile;           // Input stream
  int next;           // Next char in the input stream
  vector<int> freqs(256, 0);       // Count of each char found

  // Open input filestream
  string inputFileName = argv[1];
  inputFile.open(inputFileName);

  // Reconstruct the freqs vector to reconstruct the Huffman tree
  for (int i = 0; i < 256; i++) {
    inputFile >> next;
    if (inputFile.eof()) break;
    freqs[i] = next;
  }

  // Reconstruct the Huffman tree
  HCTree huffman;
  huffman.build(freqs);

  // Open the output file for writing
  ofstream outputFile;                  // Output stream
  string outputFileName = argv[2];      // Name of output file
  outputFile.open(outputFileName);

  while (1) {

    // Read the next byte
    int result = huffman.decode(inputFile);
    if (result == -1) break;
    outputFile << (byte) result;
  }

  // Close input and output streams
  inputFile.close();
  outputFile.close();
  return 0;
}
