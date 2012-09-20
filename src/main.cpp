#include <math.h>
#include <SDL/SDL.h>
#include <cairo/cairo.h>
#include <string>
#include <sstream>
#include <iostream>
#include "scratchio.h"

using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Itchy++";

int main(int argc, char** argv) {

	long long last = SDL_GetTicks();

	//Start the window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(WINDOW_TITLE, 0);

	SDL_Event event;

	bool itchyRunning = true;

	Stage* stage = openFromFile("project.sb");

	int r = 0;

	cairo_surface_t* crs = cairo_image_surface_create_for_data(
		(Uint8*) screen->pixels,
		CAIRO_FORMAT_ARGB32,
		screen->w,
		screen->h,
		screen->pitch);

	while (itchyRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				itchyRunning = false;
			}
		}

		stringstream caption;
		caption << "FPS: " << 1.0 / (SDL_GetTicks() - last) * 1000;

		last = SDL_GetTicks();


		// BEGIN RENDERING

		SDL_LockSurface(screen);

		cairo_t* cr = cairo_create(crs);

		cairo_set_source_rgb(cr, 255, 255, 255);
		cairo_paint(cr);

		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_move_to(cr, 550, 20);
		cairo_set_font_size(cr, 10);
		cairo_show_text(cr, caption.str().c_str());

		stage->drawOn(cr);

		cairo_destroy(cr);

		SDL_UnlockSurface(screen);

		// END DRAWING

		SDL_Flip(screen);

		SDL_Delay(1000/60);
	}
	SDL_Quit();
	return 0;
}