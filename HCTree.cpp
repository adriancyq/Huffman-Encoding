/*
* File:         HCTree.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/15/2017
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
  HCNode * newLeaf;

  // Initialize forest of one node trees
  for (int i = 0; i < freqs.size(); i++) {
    if (freqs[i]) {
      newLeaf = new HCNode(freqs[i], i);
      leaves[i] = newLeaf;
      treeBuilder.push(newLeaf);
    }
  }

  // construct the Huffman tree
  while (treeBuilder.size() > 1) {

    // Select two smallest-count roots
    HCNode * t1 = treeBuilder.top();
    treeBuilder.pop();
    HCNode * t2 = treeBuilder.top();
    treeBuilder.pop();

    // Create a new parent node for smallest-count roots
    int total = t1->count + t2->count;
    HCNode * parent = new HCNode(total, 0, t2, t1);
    t1->p = parent;
    t2->p = parent;
    treeBuilder.push(parent);
  }

  // The remaining node in the queue will be set as root
  if (treeBuilder.size() == 1) {
    root = treeBuilder.top();
  }
}


/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void encode(byte symbol, BitOutputStream& out) const {
  HCNode * current = leaves[symbol];
  stack<int> encoding;

  // Follow the path from leaf to root
  while (current != root) {

    // Determine whether we took a 0 or 1 to go up
    if (current->isZeroChild()) {
      encoding.push(0);
    }
    else {
      encoding.push(1);
    }

    // Move up one level
    current = current->p;
  }

  // Write out the contents of the stack into the ofstream
  while (!encoding.empty()) {
    out.writeBit(encoding.top());
    encoding.pop();
  }
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int decode(BitInputStream& in) const {
  int nextBit;
  HCNode * current = root;

  // Traverse until we hit a leaf node
  while (!current->isLeaf()) {
    nextBit = in.readBit();
    if (in.eof()) return -1;

    // Go down the appropriate path, depending on the "bit" read
    if (nextBit == 0) {
      current = current->c0;
    }
    else if (nextBit == 1){
      current = current->c1;
    }
  }

  // Hit a leaf, get the symbol
  return (int) current->symbol;
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
