#include <iostream>
#include <fstream>
#include <vector>
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

  ifstream inputFile;              // Input stream
  unsigned int next;               // Next char in the input stream
  vector<int> freqs(256, 0);       // Count of each char found

  // Open input filestream
  string inputFileName = argv[1];
  inputFile.open(inputFileName);

  // Read file
  while (1) {
    next = (unsigned int) inputFile.get();
    if (inputFile.eof()) break;
    freqs[next]++;
  }

  // Close the input filestream
  inputFile.close();

  // Build the Huffman tree using the populated frequency vector
  HCTree huffman;
  huffman.build(freqs);

  // Open output filestream
  ofstream outputFile;                  // Output stream
  string outputFileName = argv[2];      // Name of output file
  outputFile.open(outputFileName);

  // Write out the frequencies in the output file for decoding
  for (int i = 0; i < 256; i++) {
    outputFile << freqs[i] << endl;
  }

  // Reopen the input file again
  ifstream secondPass;
  secondPass.open(inputFileName);

  // Read in each byte and "encode" it
  while (1) {
    next = (unsigned int) secondPass.get();
    if (secondPass.eof()) break;
    cerr << next << endl;

    // Write the encoded symbol to output file
    huffman.encode((unsigned char) next, outputFile);
  }

  // Close input and output streams
  outputFile << endl;
  secondPass.close();
  outputFile.close();

  return 0;
}
