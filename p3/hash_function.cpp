/* This assignment originated at UC Riverside.*/

/**
 * @file  hash_function.cpp  Hash function.
 *
 *  @brief
 *        Implements a hash function that I found
 *  at : http://www.partow.net/programming/hashfunctions/.
 *  According to the authors of the website, the best results 
 *  have been found to include the use of prime numbers. It states
 *  that when a set of random number is multiply by a prime number
 *  the result shall show no bias towards one state or another, when 
 *  anaylzed at their bit levels. Which I believe is exactly what we want;
 *  to get as close as we can to a simple uniform distribution. This
 *  algorithm by Rober Sedgwicks did speed up the hashing quite a bit.
 *  However, I have to admit that it didn't do such a perfect job at our
 *  objective, which is uniform distribution. There were more collisions
 *  than expected but the longest list ever is kept in tact. So to sum it up, 
 *  this hash function did not distribute to some empty slots but it did 
 *  try to keep the linked list short. I stumble upon this with my research
 *  to the best hash function while researching on google.
 *  @author (Modified by) Athit Vue
 *  @date 3/25/2016
 */
 
#include <string>
#include "hash.h"

using std::string;

// This is only a sample hash function (and a bad one at that). You will
// need to replace the contents of this hash function with your own 
// hash function

/**
 *  Hash::hf.
 *
 *  Implementation of the hash function.
 *
 *  @param ins  5-letter words.
 *  @return int   
 */
int Hash::hf ( string ins ) 
{
  int b = 378551;
  int a = 63689;
  unsigned int hash = 0;
  for (size_t i = 0; i < ins.length(); i++)
  {
    hash = (hash * a) + ins[i];
    a = a * b;
  }
  
  return hash % HASH_TABLE_SIZE;
  //simple hash function
  //return ( (int) ins[0] ) % HASH_TABLE_SIZE;
}

