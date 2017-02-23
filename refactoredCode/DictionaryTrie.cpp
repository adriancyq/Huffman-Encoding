/*
 * File:      DictionaryTrie.cpp in refactoredCode
 * Authors:   Jonathan Chiu (A12113428), Adrian Cordova (A12010305)
 * Class:     CSE 100, Winter 2017
 * Date:      2/7/2017
 *
 * Implementation of a multiway trie and its node. Supports insertion, lookup,
 * and completion prediction, given a prefix string.
 *
 */

#include "util.h"
#include "DictionaryTrie.h"
#define LETTERS 26
#define ALPHABET 27
#define SPACE 26

 /*refactored things
    got rid of magic numbers
    enhanced variable names
  */

/*
 * Constructor function for a multiway trie node.
 */
MWTNode::MWTNode()
{
  int zero = 0;
  endWord = false;
  frequency = zero;

  // Initialize the children
  for(int i = zero; i < ALPHABET; i++) {
      children[i] = NULL;
  }
}

/*
 * Constructor function for a multiway trie.
 */
DictionaryTrie::DictionaryTrie()
{
  root = new MWTNode();
}

/*
 * Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string)
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  int zero = 0;
  int twentysix = 26;
  MWTNode * currentNode = root;       // Current position in trie
  int nextPostion;                       // Index of next child

  // Nothing to insert
  if (word.length() == zero) { return false; }

  // Traverse down the trie
  for (unsigned int level = zero; level < word.length(); level++) {
    nextPostion = word[level] - 'a';

    // Next char is space
    if (word[level] == ' ') {
      nextPostion = SPACE;
    }

    // Invalid char
    if (nextPostion < zero || nextPostion > twentysix) {
      return false;
    }

    // Create a new node at current position if there is none
    if (!currentNode->children[nextPostion]) {
      currentNode->children[nextPostion] = new MWTNode();
    }

    // Move down one level
    currentNode = currentNode->children[nextPostion];
  }

  // Check if the word was already inserted
  if (currentNode->endWord) {

    // Return false to indicate word already exists
    currentNode->frequency = freq;
    return false;
  }

  // Mark end of word
  currentNode->frequency = freq;
  currentNode->endWord = true;
  currentNode->word = word;
  return true;
}

/*
 * Determine whether a given string is in the dictionary.
 * Return true if word is in the dictionary, and false otherwise
 */
bool DictionaryTrie::find(std::string word) const
{
  int zero = 0;
  int twentysix = 26;
  // Check for invalid (empty) strings
  if (word.length() == zero) { return false; }

  // Current position in the trie
  MWTNode * currentNode = root;
  int nextPosition;

  // Traverse down valid paths within the trie
  for (unsigned int level = zero; level < word.length(); level++) {
    if (!currentNode) { return false; }

    // Move down a level
    nextPosition = word[level] - 'a';

    // Next char is space
    if (word[level] == ' ') {
      nextPosition = SPACE;
    }

    // Invalid char
    if (nextPosition < zero || nextPosition > twentysix) {
      return false;
    }

    currentNode = currentNode->children[nextPosition];
  }

  if (!currentNode) { return false; }

  // Found our word
  if (currentNode->endWord) { return true; }

  // Word is not in the trie
  return false;
}

/*
 * Given a string prefix, determine most likely possible completions.
 *
 * Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(
  std::string prefix,
  unsigned int num_completions)
{
  std::vector<std::string> words;   // Container for most frequent words
  unsigned int zero = 0;
  // Check for empty string
  if (prefix.empty()) {
    std::cerr << "Invalid Input. Please retry with correct input" << std::endl;
    return words;
  }

  MWTNode * currentNode = root;         // Current position in Trie
  int nextPosition;

  // Keep in sorted order the most frequent completions
  std::priority_queue<std::pair<std::string, int>,
    std::vector<std::pair<std::string, int>>,
    CompareFrequencies>
      mostFrequent;

  // Traverse to the given prefix in the trie
  for (unsigned int level = zero; level < prefix.length(); level++) {
    if (currentNode == NULL) { return words; }
    nextPosition = prefix[level] - 'a';
    currentNode = currentNode->children[nextPosition];
  }

  // Begin looking for completed words with DFS
  std::stack<MWTNode*> stack;
  stack.push(currentNode);
  while (!stack.empty()) {
    currentNode = stack.top();
    stack.pop();

    // Found a word, push to priority queue
    if (currentNode->endWord) {
      std::pair<std::string, int> foundWord(currentNode->word, currentNode->frequency);
      mostFrequent.push(foundWord);
    }

    // Add all existing children
    for (int i = zero; i < LETTERS; i++) {
      if (currentNode->children[i]) {
        stack.push(currentNode->children[i]);
      }
    }
  }

  // Populate the vector with "num_completions" most frequent words
  for (unsigned int index = zero; index < num_completions; index++) {
    if (!mostFrequent.empty()) {
      words.push_back(mostFrequent.top().first);
      mostFrequent.pop();
    }
  }

  return words;
}

/*
 * Destructor for the multiway trie.
 */
DictionaryTrie::~DictionaryTrie()
{
  deleteAll(root);
}

/*
 * Helper function for the destructor of the multiway trie.
 */
void DictionaryTrie::deleteAll(MWTNode * curr)
{
  int zero = 0;
  // No node to delete
  if (!curr) { return; }

  // Preorder traversal
  for (int i = zero; i < LETTERS; i++) {
    if (curr->children[i]) {
      deleteAll(curr->children[i]);
    }
  }

  // Delete the current node
  delete curr;
}
