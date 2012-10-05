#include <SDL/SDL.h>
#ifdef __APPLE__
#include "/opt/local/include/cairo/cairo.h"
#else
#include <cairo/cairo.h>
#endif
#include <sstream>
#include <math.h>

#include "Itchy.h"
#include "gui.h"


	Gui::Gui(){

	}

	void Gui::update(){

	}

	void Gui::init(Itchy* context){
		uint32_t last = SDL_GetTicks();

		//Start the window
			SDL_Init(SDL_INIT_VIDEO);
			SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
			SDL_WM_SetCaption(WINDOW_TITLE, 0);

			SDL_Event event;

			bool itchyRunning = true;

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

				render(cr, caption.str(), context);

				cairo_destroy(cr);

				SDL_UnlockSurface(screen);

				// END DRAWING

				SDL_Flip(screen);

				SDL_Delay(1000/60.0);
			}
			SDL_Quit();
	}

	void Gui::render(cairo_t* cr, string caption, Itchy* context){
		cairo_set_source_rgb(cr, 255, 255, 255);
						cairo_paint(cr);

						cairo_set_source_rgb(cr, 0, 0, 0);
						cairo_move_to(cr, 550, 20);
						cairo_set_font_size(cr, 10);
						cairo_show_text(cr, caption.c_str());

						context->getStage()->drawOn(cr);
	}




