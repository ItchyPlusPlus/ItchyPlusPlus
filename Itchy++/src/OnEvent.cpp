/*
 * OnEvent.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Benjamin
 */
#include "Itchy.h"

void Itchy::OnEvent(SDL_Event* Event) {
	if(Event->type == SDL_QUIT) {
	        Running = false;
	}
}
