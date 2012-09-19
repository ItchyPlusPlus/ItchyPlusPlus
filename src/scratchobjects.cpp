#include "scratchobjects.h"

Scriptable::Scriptable(ObjectRecord* record) {
	this->name = (char*) record->fields[6]->data;
	cout << "My name is: " << name << endl;
}

Stage::Stage(ObjectRecord* record) : Scriptable(record){
	ObjectRecord* sprites = record->fields[16];
	for (uint32_t i = 0; i < sprites->fieldCount; i++) {
		new Sprite(sprites->fields[i]);
	}
}

Sprite::Sprite(ObjectRecord* record) : Scriptable(record){
	//this->name = (char*) record->fields[6]->data;
}
