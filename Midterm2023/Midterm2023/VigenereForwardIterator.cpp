// VigenereForwardIterator.cpp

#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream)
    : fIStream(aIStream),     // Initialize the iVigenereStream reference member
    fCurrentChar(0),        // Initialize the current character to null
    fEOF(aIStream.eof())    // Set fEOF based on the initial state of the iVigenereStream
{

    // If the stream is not at the end, read the first character into fCurrentChar
    if (!fEOF)
    {
        fIStream >> fCurrentChar;
    }

}

// Dereference operator to get the current character
char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;
}

// Prefix increment operator (++iter)
VigenereForwardIterator& VigenereForwardIterator::operator++()
{
    fIStream >> fCurrentChar;
    fEOF = fIStream.eof();
    return *this;
}

// Postfix increment operator (iter++)
VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

// Equality operator (iter1 == iter2)
// Compare the iVigenereStream references and the fEOF states
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
    return (&fIStream == &aOther.fIStream) && (fEOF == aOther.fEOF);
}

// Inequality operator (iter1 != iter2)
// Invert the result of the equality operator
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
    return !(*this == aOther);
}

// Begin iterator (start of the stream)
VigenereForwardIterator VigenereForwardIterator::begin() const
{
    // Create a copy of the current iterator
    VigenereForwardIterator result = *this;

    // Reset the iVigenereStream position to the beginning
    result.fIStream.reset();

    // Update fEOF based on whether the stream has reached the end after resetting
    result.fEOF = result.fIStream.eof();

    // If the stream is at the end, return result or if not, read the first character into fCurrentChar
    if (result.fEOF)
    {
        return result; // Return the new iterator at the beginning
    }
    else
    {
        result.fIStream >> result.fCurrentChar;
    }
}

// End iterator (end of the stream)
VigenereForwardIterator VigenereForwardIterator::end() const
{
    VigenereForwardIterator result = *this;

    // Set fEOF to true to indicate the end of the stream
    result.fEOF = true;
    return result;  // Return the new iterator at the end
}