#ifndef GUI_H_
#define GUI_H_

#include <SDL/SDL.h>
#ifdef __APPLE__
#include "/opt/local/include/cairo/cairo.h"
#else
#include <cairo/cairo.h>
#endif
#include <sstream>
#include <math.h>

using namespace std;

#include "Itchy.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class Gui {
public:
	Gui();
	void init(Itchy*);
	void update();
private:
	void render(cairo_t*, string, Itchy*);
};


#endif
