#include <math.h>
#include <SDL/SDL.h>
#include <cairo/cairo.h>
#include <string>
#include <sstream>

using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Itchy++";

//FPS thing (Debugging Purposes Only)
class Timer{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    
    Timer(){
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
    }

    void start(){
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
    }
    void stop(){
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
    }
    void pause(){
    if( ( started == true ) && ( paused == false ) ){
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
    }
    void unpause(){
        if( paused == true ){
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
    }

    int get_ticks(){
        if( started == true ){
        if( paused == true ){
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }
    //If the timer isn't running
    return 0;
    }

    bool is_started(){
        return started;
    }
    bool is_paused(){
        return paused;
    }
};

int main(int argc, char** argv) {

        //Keep track of the frame count
        int frame = 0;
        
        //Timer used to calculate the frames per second
        Timer fps;

        //Timer used to update the caption
        Timer update;
        
        //Start the update timer
        update.start();
        
        //Start the frame timer
        fps.start();
        
        
        //Start the window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(WINDOW_TITLE, 0);

	SDL_Event event;

	bool itchyRunning = true;

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
                //Increase the frame counter
                frame++;
                
                //If a second has passed since the caption was last updated
                if( update.get_ticks() > 1000 ){
                //The frame rate as a string
                stringstream caption;

                //Calculate the frames per second and create the string
                 caption << "Average Frames Per Second: " << frame / ( fps.get_ticks() / 1000.f );

                //Reset the caption
                SDL_WM_SetCaption( caption.str().c_str(), NULL );

                //Restart the update timer
                update.start();
                }
                
                //Render the stuff.

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

		cairo_destroy(cr);

		SDL_UnlockSurface(screen);

		SDL_Flip(screen);

		SDL_Delay(1000/30);
	}
	SDL_Quit();
	return 0;
}