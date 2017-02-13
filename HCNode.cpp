/*
* File:         HCNode.cpp
* Authors:      Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
* Class:        CSE 100, Winter 2017
* Date:         2/13/2017
*
* Implementation of Huffman code nodes for the Huffman tree.
*/
#include "HCNode.h"
#include <iostream>

using namespace std;

/*
 * Comparator operator for the Huffman node. Symbols with lower frequency
 * have a higher priority. If two symbols have the same frequency, the one
 * with the higher ASCII value has higher frequency.
 * Return true if this node has higher count (and lower priority) than the
 * other node, or this node's symbol has a lower ASCII value (if the two
 * counts are the same); false otherwise.
 */
bool HCNode::operator<(const HCNode& other)
{
  // Counts are different, lower count has higher priority
  if (count != other.count) {
    return count > other.count;
  }

  // Counts are same, compare by symbol
  return symbol > other.symbol;
}

/*
 * Check if the current node is a zero child of the parent. Return true if so,
 * or false otherwise.
 */
bool HCNode::isZeroChild()
{
  if (p->c0 == this) { return true; }
  return false;
}

/*
 * Check if the current node is a leaf.
 */
bool HCNode::isLeaf()
{
  return !c0 && !c1;
}
