/*
* File:         HCTree.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/13/2017
*
* Implementation of Huffman algorithm to build the Huffman coding tree, as
* well as encoding and decoding.
*/

#include "HCNode.h"
#include "HCTree.h"
#include <queue>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

/*
 * Use the Huffman algorithm to build a Huffman coding tree.
 * Freqs is a vector of ints such that freqs[i] is the frequency of
 * occurrence of byte i in the message. This method should assign to
 * root the root of the huffman coding tree and have leaves[i] pointing
 * to the leaf node containing byte i.
 */
void HCTree::build(const vector<int> & freqs)
{
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> treeBuilder;

  // Initialize forest of one node trees
  for (int i = 0; i < 256; i++) {
    if (freqs[i] != 0) {
      leaves[i] = new HCNode(freqs[i], i);
      treeBuilder.push(leaves[i]);
    }
  }

  // Next lowest and second lowest priority HCNodes
  HCNode* t1 = NULL;
  HCNode* t2 = NULL;
  HCNode* parent;

  // construct the Huffman tree
  while (treeBuilder.size() > 1) {

    // Select two smallest-count roots
    t1 = treeBuilder.top();
    treeBuilder.pop();
    t2 = treeBuilder.top();
    treeBuilder.pop();

    // Create a new parent node for smallest-count roots
    parent = new HCNode((t1->count + t2->count), 0, t1, t2, NULL);
    t1->p = parent;
    t2->p = parent;
    treeBuilder.push(parent);
  }

  // Priority queue will now only contain the root of the Huffman tree
  root = treeBuilder.top();
  treeBuilder.pop();
}


/*
 * Write to the given ofstream the sequence of bits coding the given symbol.
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
  HCNode * current = leaves[symbol];
  stack<unsigned char> encoding;

  // Follow the path from leaf to root
  while (current->p) {

    // Determine whether we took a 0 or 1 to go up
    if (current->isZeroChild()) { encoding.push('0'); }
    else { encoding.push('1'); }

    // Move up one level
    current = current->p;
  }

  // Write out the contents of the stack into the ofstream
  while (!encoding.empty()) {
    out << (unsigned char) encoding.top();
    encoding.pop();
  }
}

/*
 * Return the symbol coded in the next sequence of bits that are represented
 * as ASCII text from the ifstream.
 */
int HCTree::decode(ifstream& in) const
{
  int nextBit;
  HCNode * current = root;

  // Traverse until we hit a leaf node
  while (!current->isLeaf()) {
    nextBit = in.get();           // Next bit in input stream
    if (in.eof()) { return -1; }                  // Hit end of file

    // Go down the appropriate path, depending on the "bit" read
    if (nextBit == '0') {
      current = current->c0;
    }
    else {
      current = current->c1;
    }
  }

  // Hit a leaf, get the symbol
  return current->symbol;
}

/*
 * Destructor function for the Huffman tree.
 */
HCTree::~HCTree()
{
  helperDestructor(root);
}

 /*
  * Recursive helper function for the destructor using postorder traversal.
  */
void HCTree::helperDestructor(HCNode* current)
{
  if (!current) { return; }

  // Go left first
  helperDestructor(current->c0);

  // Then go right
  helperDestructor(current->c1);

  // Delete current
  delete current;
}
