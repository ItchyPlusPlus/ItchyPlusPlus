#include <math.h>
#include <SDL/SDL.h>
#include <cairo/cairo.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


#include "scratchio.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Itchy++";

int main(int argc, char** argv) {

	long long last = SDL_GetTicks();

	//Start the window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(WINDOW_TITLE, 0);
        cout << "Window Started." << endl;

	SDL_Event event;

	bool itchyRunning = true;

	openFromFile("project.sb");

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

		cairo_save(cr);
		cairo_set_source_rgb(cr, 0, 255, 0);
		cairo_translate(cr, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		cairo_rotate(cr, r++ * (M_PI/180));
		cairo_rectangle(cr, -40, -40, 80, 80);
		cairo_fill(cr);
		cairo_restore(cr);

		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_move_to(cr, 0, 20);
		cairo_set_font_size(cr, 20);
		cairo_show_text(cr, "Itchy++ Dev.");

		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_move_to(cr, 550, 20);
		cairo_set_font_size(cr, 10);
		cairo_show_text(cr, caption.str().c_str());

		cairo_destroy(cr);

		SDL_UnlockSurface(screen);

		// END DRAWING

		SDL_Flip(screen);

		//SDL_Delay(1000/60);
	}
	SDL_Quit();
	return 0;
}
