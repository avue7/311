#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "vector.h"

using namespace std;

bool Vector::sort_by(const Vector& a, const Vector& b)
{
  return a.name < b.name;
}

int main()
{
  Vector v;
  string name;
  int number;
  vector<Vector>m_v;
  for (int i = 0; i < 3; i++)
  {
    cout << "enter name" << endl;
    cin >> name;
    cout << "enter int" << endl;
    cin >> number;
    
    v.name = name;
    v.key = number;
    
    m_v.push_back(v);
  }
  
  vector<Vector>::iterator it;
  
  for(it = m_v.begin(); it != m_v.end(); it++)
  {
    cout << "Before the sort: " << it->name << endl;
  }
  
  sort(m_v.begin(), m_v.end(), sort_by);
  
  for(it = m_v.begin(); it != m_v.end(); it++)
  {
    cout << "After the sort: " << it->name << endl;
  }
  
  
  return 0;
}