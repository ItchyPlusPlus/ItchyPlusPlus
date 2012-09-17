#ifndef SCRATCHIO_H__
#define SCRATCHIO_H__

#include <iostream>
#include <fstream>
#include <stdint.h>

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
private:
	istream* stream;

	void readBlock(void* block, uint32_t);
};

#endif
