#ifndef SCRATCHOBJECTS_H__
#define SCRATCHOBJECTS_H__

#include <cairo/cairo.h>
#include <sstream>


class Scriptable;
class Stage;
class Sprite;

class Media;
class Image;

class Form;

#include "scratchio.h"

class Scriptable {
public:
	Scriptable(ObjectRecord*);
	void drawOn(cairo_t*);

	char* name;
	Stage* stage;

	Image** images;
	uint32_t imageCount;
};

class Stage : public Scriptable {
public:
	Stage(ObjectRecord*);

	void drawOn(cairo_t*);
private:
	Sprite** sprites;
	uint32_t spriteCount;
	int32_t centerx;
	int32_t centery;
};

class Sprite : public Scriptable {
public:
	Sprite(ObjectRecord*, Stage*);

	void drawOn(cairo_t*);
private:
    double x;
    double y;
    double rotation;
};


class Media {
public:
	Media(ObjectRecord*);

	char* name;
};

class Image : public Media {
public:
	Image(ObjectRecord*);

	void drawOn(cairo_t*);
	Form* form;
	int32_t centerx;
	int32_t centery;
};

class Form {
public:
	Form(ObjectRecord*);

	uint32_t* decompress(uint8_t*, uint32_t);
	void drawOn(cairo_t*);
private:
	uint32_t decodeInt(ByteStream*);
	uint32_t* resizeBitmap(uint32_t*, uint32_t);

	cairo_surface_t* image;

	uint32_t width;
	uint32_t height;

	uint8_t depth;

	uint32_t bitmapSize;
};

#endif
