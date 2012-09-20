#ifndef SCRATCHIO_H__
#define SCRATCHIO_H__

#include <algorithm>
#include <endian.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>
#include <streambuf>
#include <istream>
#include <ostream>

struct OSB;
class ByteStream;
class ObjectRecord;
class ScratchReader;

#include "scratchobjects.h"

using namespace std;

Stage* openFromFile(const char*);
Stage* openFromStream(istream*);

struct OSB : public std::streambuf {
    OSB(uint8_t*, size_t);
};

class ByteStream {
public:
	ByteStream(istream*);
	ByteStream(uint8_t*, uint32_t);
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
	ObjectRecord(uint8_t, uint8_t, char*, uint32_t, ObjectRecord**, uint32_t);
	uint8_t id;
	uint8_t version;
	char* data;
	uint32_t dataSize;
	ObjectRecord** fields;
	uint32_t fieldCount;
};

class ScratchReader {
public:
	ScratchReader(ByteStream*);
	Stage* readProject();
	ObjectRecord* readObjectStore();
	ObjectRecord* readObject();
	ObjectRecord* readFixedFormat(uint8_t);
private:
	ByteStream* stream;
};

#endif
