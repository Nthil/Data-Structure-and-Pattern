#include "ShakerSortableIntVector.h"

ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : SortableIntVector(aArrayOfIntegers, aNumberOfElements)
{
}

void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
    size_t left = 0; 
    size_t right = (*this).size() - 1; 

    while (left < right)
    {
        for (size_t i = left; i < right; i++) 
        {
            if (!aOrderFunction(get(i + 1), get(i))) 
            {
                (*this).swap(i, i + 1);
            }
        }

        right--;

        for (size_t i = right; i > left; i--) 
        {
            if (!aOrderFunction(get(i), get(i - 1))) 
            {
                (*this).swap(i - 1, i);
            }
        }

        left++;
    }
}
