/**
 * @file party.cc
 *
 * @brief
 *    Party class functions
 *
 * @author Athit Vue
 * @date 2/05/2016
 */

#include "party.h"

Party::Party(int numDiners, const string& reservationName, int timeRequired)
{
    this->numDiners = numDiners;                
    this->timeRequired = timeRequired;
    this->reservationName = new string;
    *this->reservationName = reservationName;
}

Party::~Party()
{
    delete this->reservationName;
}
