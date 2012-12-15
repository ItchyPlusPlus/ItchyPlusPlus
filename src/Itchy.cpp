#include "Itchy.h"

Itchy::Itchy(int argc, char** argv) {
	const char* PROJECT;
    if(argc == 1) {
        PROJECT = "project.sb";
    } else {
        PROJECT = argv[1];
    }

    uint32_t start = SDL_GetTicks();
    this->stage = openFromFile(PROJECT);
    cout << "Read time: " << SDL_GetTicks() - start << "ms" << endl;

    Gui gui;
    gui.init(this);
}

Stage* Itchy::getStage() {
	return this->stage;
}


