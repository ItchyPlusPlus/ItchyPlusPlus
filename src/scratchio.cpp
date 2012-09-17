#include "scratchio.h"

ByteStream::ByteStream(istream* stream) {
	this->stream = stream;
}

uint8_t ByteStream::uint8() {
	uint8_t n;
	this->readBlock(&n, sizeof(uint8_t));
	return n;
}

uint16_t ByteStream::uint16() {
	uint16_t n;
	this->readBlock(&n, sizeof(uint16_t));
	return n;
}

uint32_t ByteStream::uint32() {
	uint32_t n;
	this->readBlock(&n, sizeof(uint32_t));
	return n;
}

uint64_t ByteStream::uint64() {
	uint64_t n;
	this->readBlock(&n, sizeof(uint64_t));
	return n;
}

int8_t ByteStream::int8() {
	int8_t n;
	this->readBlock(&n, sizeof(int8_t));
	return n;
}

int16_t ByteStream::int16() {
	int16_t n;
	this->readBlock(&n, sizeof(int16_t));
	return n;
}

int32_t ByteStream::int32() {
	int32_t n;
	this->readBlock(&n, sizeof(int32_t));
	return n;
}

int64_t ByteStream::int64() {
	int64_t n;
	this->readBlock(&n, sizeof(int64_t));
	return n;
}

float ByteStream::float32() {
	float n;
	this->readBlock(&n, sizeof(float));
	return n;
}

double ByteStream::float64() {
	double n;
	this->readBlock(&n, sizeof(double));
	return n;
}

void ByteStream::readBlock(void* block, uint32_t size) {
	this->stream->read((char*) block, size);
}

void openFromFile(const char* path) {
	ifstream::pos_type size;

    ifstream file(path, ios::in|ios::binary);

    if (file.is_open()) {
		openFromStream(&file);

        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void openFromStream(istream* s) {
	ByteStream stream(s);
ahea
	for (int i = 0; i < 10; i++) {
		cout << (char) stream.uint8();
	}

	cout << endl;
}
