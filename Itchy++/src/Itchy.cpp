/*
 * Itchy.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: lolzballs
 */
#include "Itchy.h"

Itchy::Itchy(){
	Running = true;
	Surf_Display = NULL;
}

// OnEvent Function
void Itchy::OnEvent(SDL_Event* Event) {
	if(Event->type == SDL_QUIT) {
	        Running = false;
	}
}

// OnLoop Function
void Itchy::OnLoop() {

}

// OnCleanup Function
void Itchy::OnCleanup() {
	SDL_Quit();
}

//OnRender Function
void Itchy::OnRender() {

}

//OnInit Function
bool Itchy::OnInit(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	        return false;
	    }

	    if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
	        return false;
	    }

	    return true;
}

//OnExecute Function
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

/*MAIN Function
 * Starts the GUI using the OnExecute function
 */
int main(int argc, char* argv[]) {
	Itchy theApp;
	return theApp.OnExecute();
}
