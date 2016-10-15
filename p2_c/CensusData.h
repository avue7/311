
/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <fstream>
#include <vector>
#include <string>

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();        
   void initialize(std::ifstream&);       // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      std::string* city;
      std::string* state;
      int population;
      Record(std::string&, std::string&, int);
      ~Record();
   };
   std::vector<Record*> data;             // data storage
//
// You may add private helper functions here - do not change anything above!!
//
    private:
        void mergeSort(int p, int q, int type);
        void merge(int p, int q, int r, int type);
        void quickSort(int p, int r, int type);
        int partition(int p, int r, int type);
};

#endif // CSCI_311_CENSUSDATA_H



