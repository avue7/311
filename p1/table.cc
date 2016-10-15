/**
 * @file table.cc
 *
 * @brief
 *    The table class functions
 *
 * @author Athit Vue
 * @date 2/05/2016
 */

#include "table.h"

/**
 * Dynamically allocate memory for new string (need this for code to not seg fault).
 *  Then assign pointer member variable to point to it
 */
Table::Table(const string& tableID, int numSeats, const string& serverName)
{
    this->tableID = new string; 
    *this->tableID = tableID;
    this->serverName = new string;
    *this->serverName = serverName;
    this->numSeats = numSeats;
}

Table::~Table()
{
    delete this->tableID;
    delete this->serverName;
}

void Table::seatParty(const Party* newParty)
{
   if(getParty() == nullptr)
   {
       return;
   }
   else
   {
       this->party = newParty;
      
   }
}