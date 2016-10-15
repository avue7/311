/**
 * @file main.cpp Main file to test MinPriorityQ
 *
 * @brief
 *            This main file is used to test the MinPriorityQ.
 * It contains the test driver.
 * @author Athit Vue
 * @date 5/02/2016
 */

#include "minpriority.h"
using std::cout;
using std::endl;
using std::cin;

/**
 * main()
 * 
 * This main() tests the MinPriorityQ to make sure that
 * it works. This test driver will add an element to the 
 * min-heap with the given key value. It will update the
 * element specified by the string with the new key value.
 * The test driver will also extract and print the minimum
 * priority element and can also quit the program with 
 * typing a command of 'q'.
 */
int main()
{
  //int count = 0;
  char command;
  string id;
  int key;
  MinPriorityQ min_pq;
  
  while(cin >> command)
  {
    if(command == 'a')
    {
      cin.ignore();
      cin >> id;
      cin >> key;
      min_pq.insert(id, key);
      /*Count is for testing*/
      //count++; 
      //cout << "count is " << count << endl;
      continue;
    }
    else if(command == 'd')
    {
      cin >> id; 
      cin >> key;
      min_pq.decreaseKey(id, key);
    }
    else if(command == 'x')
    {
      string id = min_pq.extractMin();
      cout << id << endl;
    }
    /*Command v and p are for testing purposes*/
    /*else if (command == 'v')
    {
      cout << "vector size is : " << min_pq.getVectorSize() << endl;
    }
    else if (command == 'p')
    {
      min_pq.print();
    } */
    else 
    {
      break;
    }
  }

  return 0;
}