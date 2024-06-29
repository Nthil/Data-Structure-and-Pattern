#include "Vigenere.h"

void Vigenere::initializeTable()
{
	char row = 0;

	// Fill the Vigenere mapping table with characters in a circular pattern
	while (row < CHARACTERS)
	{
		char currentChar = 'B' + row;
		char col = 0;

		while (col < CHARACTERS)
		{
			// Wrap around to 'A' if the character exceeds 'Z'
			if (currentChar > 'Z')
				currentChar = 'A';
			fMappingTable[row][col] = currentChar++;
			++col;
		}
		++row;
	}
}

Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(KeyProvider(aKeyword))
{
	initializeTable();
}

// Get the current keyword by extracting characters from the keyword provider
std::string Vigenere::getCurrentKeyword()
{
	std::string current_keyword;
	size_t i = 0;

	while ( i < fKeyword.length() )
	{
		current_keyword += *fKeywordProvider;
		fKeywordProvider << *fKeywordProvider;
		++i;
	}

	return current_keyword;
}

void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter)
{
	if (!isalpha(aCharacter))
	{
		return aCharacter;
	}
		
	bool isLowerCase = std::islower(aCharacter);
	char encoded = fMappingTable[*fKeywordProvider - 'A'][std::toupper(aCharacter) - 'A'];

	// Update the keyword provider with the current character
	fKeywordProvider << aCharacter;
		
	if (isLowerCase)
	{
		return static_cast<char>(std::tolower(encoded));
	}
	return encoded;
	
}

char Vigenere::decode(char aCharacter)
{
	if (!isalpha((aCharacter)))
	{
		return aCharacter;
	}

	bool isLowerCase = std::islower(aCharacter);
	char encoded = static_cast<char>(toupper(aCharacter));
	char decoded = 0;
	char col = 0;

	while (col < CHARACTERS)
	{
		// Search for the matching decoded character in the mapping table
		if (fMappingTable[*fKeywordProvider - 'A'][col] == encoded)
		{
			decoded = static_cast<char>(col + 'A');	
			break;
		}
		++col;
		}

		fKeywordProvider << decoded;

		// Convert the decoded character back to lowercase if necessary
		if (isLowerCase)
		{
			return static_cast<char>(std::tolower(decoded));
		}
		return decoded;
}