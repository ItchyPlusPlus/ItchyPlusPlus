/*
 * Itchy.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Benjamin
 */
#include "Itchy.h"

Itchy::Itchy(){
	Running = true;
	Surf_Display = NULL;
}

int Itchy::OnExecute(){
	if(OnInit() == false) {
	        return -1;
	    }

	    SDL_Event Event;

	    while(Running) {
	        while(SDL_PollEvent(&Event)) {
	            OnEvent(&Event);
	        }

	        OnLoop();
	        OnRender();
	    }

	    OnCleanup();

	    return 0;
}

int main(int argc, char* argv[]) {
	Itchy theApp;
	return theApp.OnExecute();
}
