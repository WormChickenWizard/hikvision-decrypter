#include "hikvision.h"

// Good
unsigned char* readInBytes(std::string loc, size_t& length)
{
	std::ifstream inFile;
	inFile.open(loc, std::ios::in | std::ios::binary);
	inFile.seekg(0, std::ios::end);
	length = (size_t)inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	unsigned char* bytes = new unsigned char[length] {0};
	char* buffer = new char[length] {0};
	inFile.read(buffer, length);
	inFile.close();

	for (size_t i = 0; i < length; i++)
		bytes[i] = (unsigned char)buffer[i];

	delete[] buffer;

	return bytes;
}

// Good
void writeOutBytes(std::string loc, const unsigned char* bytes, const size_t& length)
{
	char* buffer = new char[length] {0};
	
	for (size_t i = 0; i < length; i++)
		buffer[i] = (char)bytes[i];

	std::ofstream outFile;
	outFile.open(loc, std::ios::out | std::ios::binary);
	outFile.write(buffer, length);
	outFile.close();

	delete[] buffer;

}

// Good
void decryptAES(unsigned char*& bytes, const size_t length, unsigned char* key)
{
	AES aes(128);
	unsigned char* result = aes.DecryptECB(bytes, length, key);

	delete[] bytes;
	bytes = result;
}

// Good
void encryptAES(unsigned char*& bytes, size_t& length, unsigned char* key)
{
	AES aes(128);
	unsigned int newLength = 0;
	unsigned char* result = aes.EncryptECB(bytes, length, key, newLength);

	length = newLength;
	delete[] bytes;
	bytes = result;
}

// Good
void decryptXOR(unsigned char* bytes, const size_t length, const unsigned char* key)
{

	for (size_t i = 0; i < length; i++) {
		bytes[i] ^= key[i % (sizeof(key) / sizeof(unsigned char))];
	}
}

