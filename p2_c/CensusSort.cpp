
/**
 * @file CensusSort.cpp   Sorts census population data.
 * 
 * @brief
 *    Implementation of sorting for population data. Several different types
 * of sorts are supported. This file contains driver and timing functions.
 *
 * @author Judy Challinger
 * @date 2/22/13
 */

#include <ctime>
#include <fstream>
#include <iostream>
#include "CensusData.h"

/**
 * Timing routine from
 * http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
 */
timespec diff(timespec start, timespec end)
{
   timespec temp;
   if ((end.tv_nsec-start.tv_nsec)<0) {
      temp.tv_sec = end.tv_sec-start.tv_sec-1;
      temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
   } else {
      temp.tv_sec = end.tv_sec-start.tv_sec;
      temp.tv_nsec = end.tv_nsec-start.tv_nsec;
   }
      return temp;
}

/**
 * printTime
 *
 * Prints a line of output with the timing information to sort
 * a given number of Records.
 *
 * @param records The number of Records that were sorted.
 * @param time1   The starting time.
 * @param time2   The ending time.
 */
void printTime(int records, timespec time1, timespec time2) {
   std::cout << "CPU time (seconds:nanoseconds): "
             << diff(time1,time2).tv_sec << ":"
             << diff(time1,time2).tv_nsec << " on "
             << records << " records" << std::endl;
}

/**
 * runInsertionSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * insertion sort.
 *
 * @param fp   File pointer to the census data file.
 */
void runInsertionSorts(std::ifstream& fp) {
   timespec time1, time2;
   CensusData myCensusData;

   std::cout << std::endl << "**********INSERTION SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.insertionSort(myCensusData.POPULATION);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.insertionSort(myCensusData.NAME);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
}

/**
 * runMergeSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * merge sort.
 *
 * @param fp   File pointer to the census data file.
 */
void runMergeSorts(std::ifstream& fp) {
   timespec time1, time2;
   CensusData myCensusData;
   
   std::cout << std::endl << "**********MERGE SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.mergeSort(myCensusData.POPULATION);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.mergeSort(myCensusData.NAME);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
}

/**
 * runQuickSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * quicksort.
 *
 * @param fp   File pointer to the census data file.
 */
void runQuickSorts(std::ifstream& fp) {
   timespec time1, time2;
   CensusData myCensusData;
   
   std::cout << std::endl << "**********QUICK SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.quickSort(myCensusData.POPULATION);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
   
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
   myCensusData.quickSort(myCensusData.NAME);
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), time1, time2);
   myCensusData.print();
}

/**
 * The main entry point and driver for the program. The program expects the
 * file name of a csv file to be entered on the command line. Output goes to
 * stdout - use redirection to capture it in a file.
 */
int main(int argc, char *argv[])
{
   if ( argc != 2 ) {
      std::cout << "usage: " << argv[0] << " <filename>" <<std::endl;
      return 0;
   }

   std::ifstream fp;
   fp.open(argv[1], std::ios::in);
   if (!fp.is_open()) {
      std::cout << "can't open file " << argv[1] << std::endl;
      return 0;
   }

   runInsertionSorts(fp);

   runMergeSorts(fp);

   runQuickSorts(fp);

   fp.close();
   return 0;
}
