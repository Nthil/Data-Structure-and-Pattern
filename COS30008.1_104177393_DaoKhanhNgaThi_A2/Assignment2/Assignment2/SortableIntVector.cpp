#include "SortableIntVector.h"
#include <functional>

SortableIntVector::SortableIntVector(const int* aArrayOfIntegers, size_t aNumberOfElements)
    : IntVector(aArrayOfIntegers, aNumberOfElements)
{}

void SortableIntVector::sort(std::function<bool(int, int)> aOrderFunction)
{
    for (size_t i = 0; i < size(); ++i)
    {
        for (size_t j = size() - 1; j > i; --j)
        {
            if (aOrderFunction((*this)[j - 1], (*this)[j]))
            {
                swap(j - 1, j);
            }
        }
    }
}
