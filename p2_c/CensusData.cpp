
/**
 * @file CensusData.cpp   Represents census population data.
 * 
 * @brief
 *    Stores census data and implements several different types
 * of sorts. Data can be sorted by population or by name of town. Sort
 * functions are defined in a separate file.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CensusData.h"

/**
 * Record constructor.
 * 
 * @param c The city.
 * @param s The state.
 * @param p The population.
 */
CensusData::Record::Record(std::string& c, std::string& s, int p) {
   city = new std::string(c);
   state = new std::string(s);
   population = p;
}

/**
 * Record destructor.
 */
CensusData::Record::~Record() {
   delete city;
   delete state;
}

/**
 * CensusData destructor.
 */

CensusData::~CensusData() {
   std::vector<Record*>::iterator it = data.begin();
   while (it != data.end()) {
      delete *it;
      it++;
   }
}

/**
 * CensusData::initialize.
 *
 * Rewinds to the beginning of the file. Parses each line to create a
 * Record and stores it.
 *
 * @param fp File pointer containing the census data.
 */
void CensusData::initialize(std::ifstream& fp) {
   fp.clear();
   fp.seekg(0, std::ios::beg);
   std::string line, city, state;
   int population;
   int pos1, pos2;
   CensusData::Record* record;
   while (!fp.eof()) {
      getline(fp, line);
      pos1 = line.find(',');
      city = line.substr(0, pos1);
      pos2 = line.find(',', pos1+1);
      state = line.substr(pos1+1, pos2-pos1-1);
      std::istringstream popstrm (line.substr(pos2+1), std::istringstream::in);
      popstrm >> population;
      record = new CensusData::Record(city, state, population);
      data.push_back(record);
   }
}

/**
 * CensusData::print.
 *
 * Iterates through the Records and prints the contents of each to stdout.
 */
void CensusData::print() {
   std::vector<Record*>::iterator it = data.begin();
   while (it != data.end()) {
      std::cout << *(*it)->city << ", "
                << *(*it)->state << ", "
                << (*it)->population << std::endl;
      it++;
   }
}

