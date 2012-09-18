#ifndef SCRATCHIO_H__
#define SCRATCHIO_H__

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

using namespace std;

void openFromFile(const char*);
void openFromStream(istream*);

class ByteStream {
public:
	ByteStream(istream*);
	uint8_t uint8();
	uint16_t uint16();
	uint32_t uint32();
	uint64_t uint64();
	int8_t int8();
	int16_t int16();
	int32_t int32();
	int64_t int64();
	float float32();
	double float64();

	char* readString(uint32_t);
	void readBlock(void* block, uint32_t);
	void readBlockR(void* block, uint32_t);
private:
	istream* stream;
};

class ObjectRecord {
public:
	uint8_t id;
	uint8_t version;
	uint8_t fieldCount;
};

class ScratchReader {
public:
	ScratchReader(ByteStream*);
	void readProject();
	void readObjectStore();
	void readObject();
	ObjectRecord* readField();
	void readFixedFormat(uint8_t);
private:
	ByteStream* stream;
};

#endif
