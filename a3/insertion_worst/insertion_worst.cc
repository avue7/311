#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void insertion(int* array, int size)
{
    int key;
    int i;
    for(int j = 2; j < size; j++)
    {
        key = array[j];
        i = j - 1;
        while(i > 0 && array[i] > key)
        {
            array[i + 1] = array[i];
            i = i - 1;
        }
        array[i + 1] = key;
    }
    //printing the array out
   /*for(int i = 1; i < size; i++)
    {
        cout << array[i] << endl;
    }*/
}

int main(int argc, char* argv[])
{
    int size;
    size = atoi(argv[1]);
    
    int* array = new int[size];
    
    for(int i = 1; i < size; i++)
    {
        array[i] = i;
    }
    reverse(array, (array + size));
    
    /*for(int i = 1; i < size; i++)
    {
        cout << array[i] << endl;
    }*/
    
    insertion(array, size);
    
    delete [] array;
    return 0;
}
