/**
 * @file restaurant.cc
 *
 * @brief
 *    Restaurant simulation program
 *
 * @author Athit Vue
 * @date 2/05/2016
 */
#include "restaurant.h"
#include <string>
#include <iostream>
#include <new>
#include <map>
using namespace std;

void Restaurant::getInput()
{
    string command;
    Table* table_input;
    Party* party_input;
    while(cin >> command)
    {
        if (command == "table")
        {
            string tableID;
            int num_seats;
            string server_name;
            cin >> tableID;
            cin >> num_seats;
            cin >> server_name;
            table_input = new Table (tableID, num_seats, server_name);
            available.append(table_input);
        }
        
        else if (command == "party")
        {
            string reservation_name;
            int number_diners;
            int time_required;
            cin >> number_diners;
            cin >> reservation_name;
            cin >> time_required;
            party_input = new Party(number_diners, reservation_name, time_required);
            waiting.append(party_input);
        }
        else
        {
            break;
        }
    }
}
void Restaurant::serveParties()
{
    Table* table;
    Table* occupied_table;
    Party* party;
    string server_name;
    int num_diners;
    party = waiting.first();
    table = available.first();
    
    while (!waiting.empty() || !occupied.empty())
    {
        for(occupied_table = occupied.first(); occupied_table != nullptr; occupied_table = occupied.next())
        {
            occupied_table->decrementTimer();
            int timer;
            timer = occupied_table->getTimer();
            if(timer == 0)
            {
                cout << party->getReservationName() << " finished" << endl;
                occupied_table = occupied.remove();
                occupied_table->clearTable();
                available.append(occupied_table);
            }
        }
        while (!waiting.empty() && party != nullptr && table!= nullptr)
        {   
           //for(table = available.first(); table != nullptr; table = available.next())
            while(!available.empty() && table != nullptr)
            {
                if( party->getNumDiners() <= table->getNumSeats())
                {
                    cout << *party->getReservationName() << " seated at " << *table->getTableID()<< endl;
                    table->seatParty(party);
                    table->setTimer(party->getTimeRequired());
                    num_diners = party->getNumDiners();
                    server_name = *table->getServerName();
                    servers.insert(pair<string, int>(server_name, num_diners));
                    occupied.append(table);
                    party = waiting.remove();
                    break;
                if(available.empty())
                {
                    break;
                }
                else
                {
                    table = available.next();
                }
                }
            }
        }
        if(waiting.empty()) //&& occupied.empty())
        {
            map<string, int>::iterator iter;
            for (iter = servers.begin(); iter != servers.end(); iter++)
            {
                cout << (*iter).first << " served ";
                cout << (*iter).second << endl;
            }
            break;
        }
        else
        {
            continue;
        }
    }
}
int main()
{
    Restaurant myDiner; 
    myDiner.getInput(); 
    myDiner.serveParties();
    return 0;
}




