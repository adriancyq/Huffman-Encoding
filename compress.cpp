#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  // Check that user supplied filenames
  if (argc < 2) {
    cerr << "Pass in the input file." << endl;
    return -1;
  }

  ifstream inputFile;
  string fileName = argv[1];
  unsigned char next;
  
  vector<int> freqs(256);

  // Open file
  inputFile.open(fileName);

  // Read file
  while (1) {
    inputFile >> next;
    if (inputFile.eof()) break;
    freqs[next]++;
  }

  // Close the filestream
  inputFile.close();
  
  // DEBUG: print the vector
  for (int i = 0; i < 256; i++) {
    cout << freqs[i];
  }
  
  cout << endl;
  return 0;
}
