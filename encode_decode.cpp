/** Return the symbol coded in the next sequence of bits (represented as
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
//int decode(ifstream& in) const;

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 */
//void encode(byte symbol, ofstream& out) const;

/*
 * Write to the given ofstream the sequence of bits coding the given symbol.
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
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
    out << encoding.top();
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
    nextBit = in.get();
    if (in.eof()) return -1;

    // Go down the appropriate path, depending on the "bit" read
    if (nextBit == '0') {
      current = current->c0;
    }
    else if (nextBit == '1'){
      current = current->c1;
    }
  }

  // Hit a leaf, get the symbol
  return (int) current->symbol;
}
