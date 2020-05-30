#pragma once
#include <fstream>
#include "AES.h"

unsigned char* readInBytes(const std::string, size_t&);
void writeOutBytes(std::string, const unsigned char*, const size_t&);
void decryptAES(unsigned char*&, const size_t, unsigned char*);
void encryptAES(unsigned char*&, size_t&, unsigned char*);
void decryptXOR(unsigned char*, const size_t, const unsigned char*);
