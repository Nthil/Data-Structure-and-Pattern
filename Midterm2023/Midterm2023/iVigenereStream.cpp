#include "iVigenereStream.h"

// Constructor
iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) 
	: fIStream(std::ifstream()), fCipherProvider(Vigenere(aKeyword)), fCipher(std::move(aCipher))
{
	if (aFileName != nullptr)
	{
		open(aFileName);
	}
}

// Destructor
iVigenereStream::~iVigenereStream()
{
	close();
}

// Open a file for reading
void iVigenereStream::open(const char* aFileName)
{
	fIStream.open(aFileName, std::ios::binary);
}

// Close the file
void iVigenereStream::close()
{
	fIStream.close();
}

// Reset the stream and cipher provider to the initial state
void iVigenereStream::reset()
{

	fCipherProvider.reset();
	seekstart();
}

// Check if the stream is in good condition
bool iVigenereStream::good() const
{
	return fIStream.good();
}

// Check if the stream is open
bool iVigenereStream::is_open() const
{
	return fIStream.is_open();
}

// Check if end-of-file has been reached
bool iVigenereStream::eof() const
{
	return fIStream.eof();
}

// Read characters from the file and apply the Vigenere cipher
iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	char streamCharacter = static_cast<char>(fIStream.get());

	// if read was successful, apply the Vigenere cipher on the read character
	if (fIStream) {
		aCharacter = fCipher(fCipherProvider, streamCharacter);
	}
	else {
		aCharacter = '\n'; 
	}

	return *this;
}
