/**
 *  @file hash.cpp  Functions to assist the hash function
 *
 *  @brief  
          Implements the functions to assist the hash function.
 *
 *  @author Athit Vue
 *  @date 10/19/2016
 */
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "hash.h"

using namespace std;

/**
 *  Hash constructor.
 */
Hash::Hash()
{
  runningAvgListLength = 0;
}

/** 
 *  Hash::print.
 *
 *  Iterates through the hash table and prints the values.
 */
void Hash::print()
{
  list<string>::iterator it;
  for (int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    cout << i << ":" << '\t';
    for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      cout << *it << ", ";
    }
    cout << endl;
  }
}

/**
 *  Hash::processFile.
 *
 *  Read the values in the file and insert it into the hash table.
 *
 *  @param  filename
 */
void Hash::processFile (string filename)
{
  ifstream fin;
  //convert inputs to c style string
  fin.open (filename.c_str());
  int key = 0;
  collisions = 0;
  double a = 0;
  double b = 0;
  string word;
  
  list<string>::iterator it;
  it = hashTable[key].begin();
  //while input file opened successfully
  while (fin.good())
  {
    //use getline to read word until delimiter
    getline(fin, word);
    if (word[0] != '\0') //if word exists
    {
      key = hf(word);
      //count the collisions when word is 
      //being inserted to non-empty list
      if (!hashTable[key].empty())
      {
        collisions++; //adding to collision count
        hashTable[key].push_back(word);
        runningAvgListLength = findAvgLength();
      }
      else
      {
        hashTable[key].push_back(word);
        runningAvgListLength = findAvgLength();
      }
      for (int i = 0; i < HASH_TABLE_SIZE; i++)
      {
        it = hashTable[i].begin();
        while (it != hashTable[i].end())
        {
          a++;
          it++;
        }
        if (longestList < a)
        {
          longestList = a;
        }
        b += a;
        a = 0;
      }
    }
  }
  fin.close();
}

/**
 *  Hash::search.
 *  Searches for a specific word in the hash table. If 
 *  the hash is found then return true, if it is not found
 *  then return false.
 *
 *  @param word  The word that we want to look up.
 *  @return boolean True, if found. False, if not.
 */
bool Hash::search (string word)
{
  list<string>::iterator it;
  int key = hf(word);
  it = hashTable[key].begin();
  while (it != hashTable[key].end())
  {
    if (*it == word)
    {
      return true;
    }
    it++;
  }
  return false;
}

/**
 *  Hash::remove.
 *
 *  Iterates through the hash table and remove the word 
 *  specified.
 * 
 *  @param word The word to remove fromt the hash table
 */
void Hash::remove (string word)
{
  list<string>::iterator it;
  for (int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
    {
      if (*it == word)
      {
        hashTable[i].remove(*it);
        runningAvgListLength = findAvgLength();
        return;
      }
    }
  }
}

/**
 *  Hash::findAvgLength.
 *
 *  This is a helper function to find the average of the running
 *  list length.
 *
 *  @return double Returns the average.
 */
double Hash::findAvgLength()
{
  list<string>::iterator it;
  double currentAvgListLen = 0;
  double non_empty_list = 0;
  
  for (int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    currentAvgListLen += hashTable[i].size();
    if (!hashTable[i].empty())
    {
      non_empty_list += 1;
    }
  }
  currentAvgListLen = currentAvgListLen / non_empty_list;
  runningAvgListLength = (currentAvgListLen + runningAvgListLength) / 2.0;
  return runningAvgListLength;
}

/**
 *  Hash::output.
 *
 *  This function prints the hash table to the 
 *  specify filename. The format should be exactly the 
 *  same as specified for the print() function.
 *
 *  @param  filename  The name of the output file.
 */
void Hash::output (string filename)
{
  ofstream fout;
  fout.open (filename.c_str());
  string word;
  list<string>::iterator it;
  
  for (int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    it = hashTable[i].begin();
    fout << i << ":" << '\t';
    while (it != hashTable[i].end())
    {
      fout << *it << ", ";
      it++;
    }
    fout << endl;
  }
  fout.close();
}

/**
 *  Hash::printStats.
 *
 *  Prints the hash statistics.
 */
void Hash::printStats()
{
  cout << "Total Collisions = " << collisions << endl;
  cout << "Longest List Ever = " << longestList << endl;
  cout << "Average List Length Over Time = " << runningAvgListLength << endl;
  double numb_elements = 0;
  list<string>::iterator it;
  for (int i = 0; i < HASH_TABLE_SIZE; i++)
  {
    numb_elements += hashTable[i].size();
  }
  cout << "Load Factor = " << numb_elements / HASH_TABLE_SIZE << endl;
}