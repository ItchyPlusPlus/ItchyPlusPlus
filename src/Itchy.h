#ifndef ITCHY_H_
#define ITCHY_H_

#include <SDL/SDL.h>

class Itchy;

#include "gui.h"
#include "scratchio/scratchio.h"

class Itchy {
public:
	Itchy(int, char**);
	Stage* getStage();
private:
	Stage* stage;
};


#endif
