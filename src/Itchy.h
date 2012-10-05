#include "scratchio.h"

#ifndef ITCHY_H_
#define ITCHY_H_

class Itchy{
public:
	Itchy(int, char**);
	Stage* getStage();
private:
	Stage* stage;
};


#endif /* ITCHY_H_ */
