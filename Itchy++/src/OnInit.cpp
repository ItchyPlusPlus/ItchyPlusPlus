/*
 * OnInit.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Benjamin
 */
#include "Itchy.h"

bool Itchy::OnInit(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	        return false;
	    }

	    if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
	        return false;
	    }

	    return true;
}
