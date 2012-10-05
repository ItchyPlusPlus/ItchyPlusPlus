
#ifndef GUI_H_
#define GUI_H_

#include <sstream>
#include <cairo/cairo.h>

using namespace std;

#include "Itchy.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
static const char* WINDOW_TITLE = "Itchy++";

class Gui{
public:
	Gui();
	void init(Itchy*);
	void update();
private:
	void render(cairo_t*, string, Itchy*);
};


#endif /* GUI_H_ */
