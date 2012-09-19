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
	uint32_t n;
	this->readBlockR(&n, sizeof(float));
	return htobe32(n);
}

double ByteStream::float64() {
	uint64_t n;
	this->readBlockR(&n, sizeof(double));
	return htobe64(n);
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


ObjectRecord::ObjectRecord(uint8_t id, uint8_t version, char* data, uint32_t dataSize, ObjectRecord** fields, uint32_t fieldCount) {
	this->id = id;
	this->version = version;
	this->data = data;
	this->dataSize = dataSize;
	this->fields = fields;
	this->fieldCount = fieldCount;
}

ScratchReader::ScratchReader(ByteStream* stream) {
	this->stream = stream;
}


void ScratchReader::readProject() {
	if (strcmp(this->stream->readString(10), "ScratchV02") != 0) {
		cout << "scratch project" << endl;

		cout << "info size: " << this->stream->uint32() << endl;

		ObjectRecord* infoRecord = this->readObjectStore();
		ObjectRecord* stageRecord = this->readObjectStore();

		Stage* stage = new Stage(stageRecord);
	} else {
		cout << "not scratch project" << endl;
	}
}

ObjectRecord* ScratchReader::readObjectStore() {
	if (strcmp(this->stream->readString(10), "ObjS\0Stch\0") != 0) {
		cout << "is object" << endl;

		uint32_t size = this->stream->uint32();

		cout << "object size: " << size << endl;
		ObjectRecord** table = new ObjectRecord*[size];

		for (uint32_t i = 0; i < size; i++) {
			table[i] = this->readObject();
		}

		for (uint32_t i = 0; i < size; i++) {
			ObjectRecord* object = table[i];
			ObjectRecord** fields = object->fields;
			if (fields != NULL) {
				for (uint32_t j = 0; j < object->fieldCount; j++) {
					if (fields[j]->id == 99) {
						uint32_t pointer = *(uint32_t*) fields[j]->data;
						delete fields[j];
						fields[j] = table[pointer - 1];
					}
				}
			}
		}

		return table[0];
	}
	cout << "not object" << endl;
	return NULL;
}

ObjectRecord* ScratchReader::readObject() {
	uint8_t id = this->stream->uint8();
	//cout << "id: " << (int) id << endl;
	if (id < 100) {
		return readFixedFormat(id);
	}

	uint8_t version = this->stream->uint8();

	uint8_t fieldCount = this->stream->uint8();
	ObjectRecord** fields = new ObjectRecord*[fieldCount];

	for (uint32_t i = 0; i < fieldCount; i++) {
		fields[i] = this->readObject();
	}

	return new ObjectRecord(id, version, NULL, 0, fields, fieldCount);
}

ObjectRecord* ScratchReader::readFixedFormat(uint8_t id) {
	uint32_t length = 0;

	ObjectRecord** fields = NULL;
	uint32_t fieldCount = 0;

	char* data = NULL;

	switch (id) {
	case 1: // Nil
	case 2: // True
	case 3: // False
		length = 0;
		break;
	case 4: // SmallInteger
		length = 4;
		break;
	case 5: // SmallInteger16
		length = 2;
		break;
	// long int stuff to come
	case 8: // Float
		length = 8;
		break;
	case 9: // String
	case 10: // Symbol
	case 11: // ByteArray
	case 14: // UTF8
		length = this->stream->uint32();
		break;
	case 12: // SoundBuffer
		length = this->stream->uint32() * 2;
		break;
	case 13: // Bitmap
		length = this->stream->uint32() * 4;
		break;
	case 20: // Array
	case 21: // OrderedCollection
	case 24: // Dictionary
	case 25: // IdentityDictionar
	case 32: // Point
	case 33: // Rectangle
	case 34: // Form
	case 35: // ColorForm
		switch (id) {
			case 20:
			case 21:
				length = this->stream->uint32();
				break;
			case 24:
			case 25:
				length = this->stream->uint32() * 2;
				break;
			case 32:
				length = 2;
				break;
			case 33:
				length = 4;
				break;
			case 34:
				length = 5;
				break;
			case 35:
				length = 6;
				break;
		}
		fields = new ObjectRecord*[length];
		fieldCount = length;

		for (uint32_t i = 0; i < length; i++) {
			fields[i] = this->readObject();
		}
		length = 0;
		break;
	case 30: // Color
		length = 4;
		break;
	case 31: // TranslucentColor
		length = 5;
		break;
	case 99: // ObjectRef
		length = 4;
		data = new char[length];
		data[3] = 0;
		this->stream->readBlockR(data, 3);
		break;
	default:
		cout << "Unknown field ID: " << (int) id << endl;
	}

	if (data == NULL) {
		data = new char[length];
		this->stream->readBlock(data, length);
	}

	ObjectRecord* record = new ObjectRecord(id, 0, data, length, fields, fieldCount);

	return record;
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
