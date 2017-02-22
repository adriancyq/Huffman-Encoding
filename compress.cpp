/*
* File:         compress.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/15/2017
*
* Read in the input file, build a Huffman encoding tree, and encode the
* message. Takes two command line arguments: (1) the input file, and (2) the
* output file (where we will write the encoded message).
*/
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

  ifstream inputFile;                   // Input stream
  int next;                             // Next char read
  int totalBytes = 0;                   // Total number of chars in the file
  int totalUniqueSymbols = 0;           // Total number of unique chars in file
  vector<int> freqs(256, 0);            // Count of each char found

  // Open input filestream
  string inputFileName = argv[1];
  inputFile.open(inputFileName, ios::binary);
  BitInputStream bistream(inputFile);

  // Read file to be encoded
  cout << "Reading from \"" << inputFileName << "\"... ";
  while (1) {
    next = inputFile.get();
    if (inputFile.eof()) break;
    freqs[next]++;
    totalBytes++;

    // Found a new, unique symbol
    if (freqs[next] == 1) {
      totalUniqueSymbols++;
    }
  }

  // Print stats on input file
  cout << "done." << endl;
  cout << "Found " << totalUniqueSymbols
      << " unique symbols in the input file of size "
      << totalBytes << " bytes." << endl;

  // Close the input filestream
  inputFile.close();

  // Build the Huffman tree using the populated frequency vector
  cout << "Building Huffman code tree...";
  HCTree huffman;
  huffman.build(freqs);
  cout << "done." << endl;

  // Open output filestream
  ofstream outputFile;                  // Output stream
  string outputFileName = argv[2];      // Name of output file
  outputFile.open(outputFileName, ios::binary);
  BitOutputStream bostream(outputFile);
  cout << "Writing to file \"" << outputFileName << "\"...";

  // Write out total number of unique symbols (no more than 256)
  // and total number of symbols
  bostream.writeByte(totalUniqueSymbols);
  bostream.writeInt(totalBytes);

  // Write out the frequencies in the output file for decoding
  // Optimized: Write out only the nonzero frequencies and the corresponding
  // char
  for (int i = 0; i < 256; i++) {
    if (freqs[i] > 0) {
      bostream.writeByte(i);
      bostream.writeInt(freqs[i]);
    }
  }

  // Reopen the input file again
  ifstream secondPass;
  secondPass.open(inputFileName, ios::binary);

  // Read in each byte and "encode" it
  while (1) {
    next = secondPass.get();
    if (secondPass.eof()) break;

    // Write the encoded symbol to output file
    huffman.encode((unsigned char) next, bostream);
  }

  // Ensure all bytes are written
  bostream.flush();

  // Close input and output streams
  secondPass.close();
  outputFile.close();
  cout << "done." << endl;

  // Get the filesize of the encoded file
  streampos begin, end;
  ifstream encodedFile(outputFileName, ios::binary);
  begin = encodedFile.tellg();              // Get the beginning
  encodedFile.seekg(0, ios::end);           // Move to the end
  end = encodedFile.tellg();                // Get the end
  encodedFile.close();
  int encodedFileSize = end - begin;

  cout << "Output file has size " << encodedFileSize << " bytes." << endl;

  // Get the filesize of the original file
  ifstream originalFile(inputFileName, ios::binary);
  begin = originalFile.tellg();              // Get the beginning
  originalFile.seekg(0, ios::end);           // Move to the end
  end = originalFile.tellg();                // Get the end
  originalFile.close();
  int originalFileSize = end - begin;

  // Print the compression ratio
  cout << "Compression ratio: " << (float) encodedFileSize / originalFileSize << endl;
  return 0;
}
