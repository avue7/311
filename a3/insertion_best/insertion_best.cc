#include <iostream>
#include <stdlib.h>
using namespace std;

void insertionSort(int array[], int size)
{
    int k;
    int l;
    for(int j = 2; j < size; j++)
    {
        k = array[j];
        l = j - 1;
        while (l > 0 && array[l] > k)
        {
            array[l+1] = array[l];
            l = l -1;
        }
        array[l + 1] = k;
    }
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
    insertionSort(array, size);
    delete[] array;
    return 0;
}