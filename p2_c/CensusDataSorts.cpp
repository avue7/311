
/**
 * @file CensusDataSorts.cpp   Sorts census population data.
 * 
 * @brief
 *    This file contains all of the sorting functions and their helpers.
 * 
 * @author Erik Mellum
 * @date 10/01/13
 */

#include "CensusData.h"
/**
* insertionSort uses the type variable to sort on population or city name
* @param type the type of sort to do (population or city name)
*/
void CensusData::insertionSort(int type) {
    Record* key;
    int i;
    // Checks to see whether sorting on population or city name
    if(!type)
    {
        for(int j=1; j<getSize(); j++)
        {
            key=data[j];
            i = j-1;
            // checks to see if the population at i is greater than the key population
            while(i>=0 && data[i]->population > key->population)
            {
                data[i+1]= data[i];
                i = i-1;
            }
            data[i+1] = key;
        }
    }
    else
    {
        for(int j=1; j<getSize(); j++)
        {
            key=data[j];
            i=j-1;
            while(i>=0 && *data[i]->city>*key->city)
            {
                data[i+1]= data[i];
                i = i-1;
            }
            data[i+1] = key;
        }
    }
}
/**
* mergeSort is a public interface function that uses the type variable to    
* sort on population or city name.
* @param type the type of sort to do (population or city name)
*/
void CensusData::mergeSort(int type)
{
    int p = 0;
    int r = getSize()-1;
    mergeSort(p,r,type);
}
/**
* mergeSort is a private function to perform mergeSort
* @param p, the beginning index, r, the final index,
* and type, the type of sort (city or population)
*/
void CensusData::mergeSort(int p, int r, int type)
{
    int q;
    if(p < r)
    {
        q = (p+r)/2;
        mergeSort(p,q,type);
        mergeSort(q+1,r,type);
        merge(p,q,r,type);
    }      
}
/**
* merge is a private function to perform merging in mergeSort
* @param p, the beginning index, q, the middle index,
* r, the final index, and type, the type of sort (city or population)
*/
void CensusData::merge(int p, int q, int r, int type)
{   
    int n1 = q-p +1;
    int n2 = r-q;
    std::vector<Record*> left;
    std::vector<Record*> right;
    for(int i = 0; i<n1;i++)
        left.push_back(data[p+i]);
    for(int j = 0; j<n2; j++)
        right.push_back(data[q+j+1]);
    int i=0;
    int j=0;
    for(int k=p; k<=r; k++)
    {
        if(!type)
        {
            if(left.back() != left[i-1] && (right.back() == right[j-1] ||
            left[i]->population <= right[j]->population))
            {
                data[k]=left[i];
                i=i+1;
            }
            else
            {
                data[k]=right[j];
                j=j+1;
            }
        }
        else 
        {  
            if(left.back() != left[i-1] && (right.back() == right[j-1] || 
            *left[i]->city <= *right[j]->city))
            {
                data[k]=left[i];
                i=i+1;
            }
            else
            {
                data[k]=right[j];
                j=j+1;
            }
        }
    }
}
/**
* quickSort is a sorting algorithm that uses a pivot to sort
* This method provides the public interface for quickSort
* @param type, the type of sort population or city name
*/
void CensusData::quickSort(int type) {
    int p = 0;
    int r = getSize()-1;
    quickSort(p,r,type);
}
/**
* quickSort private implementation
* @param type, the type of sort population or city name
* @param p, the beginning index
* @param r, the ending index
**/
void CensusData::quickSort(int p, int r, int type)
{
    if(p<r)
    {
        int q = partition(p,r,type);
        quickSort(p,q-1,type);
        quickSort(q+1,r,type);
    }
}
/**
* partition is a helper to the quickSort private implementation
* @param type, the type of sort population or city name
* @param p, the beginning index
* @param r, the ending index
**/
int CensusData::partition(int p, int r, int type)
{
    Record* key = data[r];
    int i = p - 1;
    for(int j = p; j <= r-1; j++)
    {
        if(!type)
        {
            if(data[j]->population <= key->population)
            {
                i=i+1;
                std::swap(data[i], data[j]);
            }    
        
        }
        else
        {
            if(*data[j]->city <= *key->city)
            {
                i=i+1;
                std::swap(data[i], data[j]);
            } 
        }
        
    }
    std::swap(data[i+1], data[r]);
    return i+1;
}


