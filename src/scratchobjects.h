#ifndef SCRATCHOBJECTS_H__
#define SCRATCHOBJECTS_H__

#include "scratchio.h"

class Scriptable {
public:
	Scriptable(ObjectRecord*);
protected:
	char* name;
};

class Stage : public Scriptable {
public:
	Stage(ObjectRecord*);
};

class Sprite : public Scriptable {
public:
	Sprite(ObjectRecord*);
};

#endif
