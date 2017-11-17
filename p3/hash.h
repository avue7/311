/* This assignment originated at UC Riverside. The hash table size
 should be defined at compile time. Use -D HASH_TABLE_SIZE=X */
 
/**
 *  @file hash.h  Declaration of the Hash class.
 *
 *  @brief
 *        Contains the prototyping of functions for hash.cpp.
 *
 *  @author (Modified by) Athit Vue
 *  @date 10/19/2016
 */
#ifndef __HASH_H
#define __HASH_H

#include <string>
#include <iostream>
#include <list>

using std::string;
using std::list;

class Hash {

public:
  Hash();                          // constructor
  void remove(string);             // remove key from hash table
  void print();                    // print the entire hash table
  void processFile(string);        // open file and add keys to hash table
  bool search(string);             // search for a key in the hash table
  void output(string);             // print entire hash table to a file
  void printStats();               // print statistics

private:
  // HASH_TABLE_SIZE should be defined using the -D option for g++
  list<string> hashTable [HASH_TABLE_SIZE];
  int collisions;                  // total number of collisions
  unsigned int longestList;        // longest list ever generated
  double runningAvgListLength;     // running average of average list length

  int hf(string);                  // the hash function

// put additional functions below as needed
// do not change anything above!
  double findAvgLength(); // function to help with finding average list length

};

#endif
