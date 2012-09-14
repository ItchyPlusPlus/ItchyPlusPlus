/*
 * Itchy.h
 *
 *  Created on: Sep 13, 2012
 *      Author: Benjamin
 */

#ifndef ITCHY_H_
#define ITCHY_H_

#include <SDL.h>

class Itchy {
private:
	bool Running;
	SDL_Surface* Surf_Display;
public:
	Itchy();
	int OnExecute();
public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
};
#endif /* ITCHY_H_ */
