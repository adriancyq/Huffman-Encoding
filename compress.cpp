#include <iostream>
#include <fstream>

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
  int nextInt;

  // Open file
  inputFile.open(fileName);

  // Read file
  while (1) {
    inputFile >> nextInt;
    if (inputFile.eof()) { break; }
    cout << nextInt;
  }

  // Close the filestream
  cout << endl;
  inputFile.close();
}
