#include "KeyProvider.h"


// Constructor
KeyProvider::KeyProvider(const std::string& keyword) : fSize(keyword.length()), fIndex(0)
{
    fKeyword = new char[fSize];
    initialize(keyword);
}


// Destructor
KeyProvider::~KeyProvider()
{
    // Clean up the dynamically allocated memory for the keyword
    delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& keyword)
{
    delete[] fKeyword;
    fSize = keyword.length();
    fKeyword = new char[fSize];
    size_t i = 0;

    while (i < fSize)
    {
       // Convert each character in the keyword to uppercase
       fKeyword[i] = std::toupper(keyword[i]);
       ++i;
    }

    fIndex = 0;
}

char KeyProvider::operator*() const
{
    // Get the current character from the keyword
    return fKeyword[fIndex];
}


// Assign a new character to the keyword
KeyProvider& KeyProvider::operator<<(char keyCharacter)
{
    fKeyword[fIndex] = std::toupper(keyCharacter);

    if (fSize - 1 == fIndex)
    {
        fIndex = 0;
    }
    else 
    {
        ++fIndex;
    }

    return *this;
}
