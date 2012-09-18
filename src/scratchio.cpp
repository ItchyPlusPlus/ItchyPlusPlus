#include "scratchio.h"

ByteStream::ByteStream(istream* stream) {
	this->stream = stream;
}

uint8_t ByteStream::uint8() {
	uint8_t n;
	this->readBlockR(&n, sizeof(uint8_t));
	return n;
}

uint16_t ByteStream::uint16() {
	uint16_t n;
	this->readBlockR(&n, sizeof(uint16_t));
	return n;
}

uint32_t ByteStream::uint32() {
	uint32_t n;
	this->readBlockR(&n, sizeof(uint32_t));
	return n;
}

uint64_t ByteStream::uint64() {
	uint64_t n;
	this->readBlockR(&n, sizeof(uint64_t));
	return n;
}

int8_t ByteStream::int8() {
	int8_t n;
	this->readBlockR(&n, sizeof(int8_t));
	return n;
}

int16_t ByteStream::int16() {
	int16_t n;
	this->readBlockR(&n, sizeof(int16_t));
	return n;
}

int32_t ByteStream::int32() {
	int32_t n;
	this->readBlockR(&n, sizeof(int32_t));
	return n;
}

int64_t ByteStream::int64() {
	int64_t n;
	this->readBlockR(&n, sizeof(int64_t));
	return n;
}

float ByteStream::float32() {
	float n;
	this->readBlockR(&n, sizeof(float));
	return n;
}

double ByteStream::float64() {
	double n;
	this->readBlockR(&n, sizeof(double));
	return n;
}

char* ByteStream::readString(uint32_t size) {
	char* string = new char[size];
	this->readBlock(string, size);
	return string;
}

void ByteStream::readBlock(void* block, uint32_t size) {
	this->stream->read((char*) block, size);
}

void ByteStream::readBlockR(void* block, uint32_t size) {
	this->readBlock(block, size);
	std::reverse((char*) block, (char*) block + size);
}


ScratchReader::ScratchReader(ByteStream* stream) {
	this->stream = stream;
}


void ScratchReader::readProject() {
	if (strcmp(this->stream->readString(10), "ScratchV02") != 0) {
		cout << "scratch project" << endl;

		cout << "info size: " << this->stream->uint32() << endl;

		this->readObjectStore();
	} else {
		cout << "not scratch project" << endl;
	}
}

void ScratchReader::readObjectStore() {
	if (strcmp(this->stream->readString(10), "ObjS\0Stch\0") != 0) {
		cout << "is object" << endl;

		uint32_t size = this->stream->uint32();

		cout << "object size: " << size << endl;

		for (int i = 0; i < size; i++) {
			this->readObject();
		}
	} else {
		cout << "not object" << endl;
	}
}

void ScratchReader::readObject() {
	uint8_t id = this->stream->uint8();
	if (id < 99) {
		readFixedFormat(id);
	}
	cout << "id: " << (int) id << endl;
}

void ScratchReader::readFixedFormat(uint8_t id) {

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
	ScratchReader reader(&stream);
	reader.readProject();
}
