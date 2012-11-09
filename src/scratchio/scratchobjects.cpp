#include "scratchobjects.h"

const uint32_t squeakColors[] = {0xffffff, 0x000000, 0xffffff, 0x808080, 0xff0000, 0x00ff00, 0x0000ff, 0x00ffff, 0xffff00, 0xff00ff, 0x202020, 0x404040, 0x606060, 0x9f9f9f, 0xbfbfbf, 0xdfdfdf, 0x080808, 0x101010, 0x181818, 0x282828, 0x303030, 0x383838, 0x484848, 0x505050, 0x585858, 0x686868, 0x707070, 0x787878, 0x878787, 0x8f8f8f, 0x979797, 0xa7a7a7, 0xafafaf, 0xb7b7b7, 0xc7c7c7, 0xcfcfcf, 0xd7d7d7, 0xe7e7e7, 0xefefef, 0xf7f7f7, 0x000000, 0x003300, 0x006600, 0x009900, 0x00cc00, 0x00ff00, 0x000033, 0x003333, 0x006633, 0x009933, 0x00cc33, 0x00ff33, 0x000066, 0x003366, 0x006666, 0x009966, 0x00cc66, 0x00ff66, 0x000099, 0x003399, 0x006699, 0x009999, 0x00cc99, 0x00ff99, 0x0000cc, 0x0033cc, 0x0066cc, 0x0099cc, 0x00cccc, 0x00ffcc, 0x0000ff, 0x0033ff, 0x0066ff, 0x0099ff, 0x00ccff, 0x00ffff, 0x330000, 0x333300, 0x336600, 0x339900, 0x33cc00, 0x33ff00, 0x330033, 0x333333, 0x336633, 0x339933};

Scriptable::Scriptable(ObjectRecord* record) {
	this->name = (char*) record->fields[6]->data;

	ObjectRecord* media = record->fields[10];

	this->imageCount = 0;
	for (uint32_t i = 0; i < media->fieldCount; i++) {
		if (media->fields[i]->id == 162) {
			this->imageCount++;
		}
	}
	this->images = new Image*[this->imageCount];

	uint32_t j = 0;
	for (uint32_t i = 0; i < media->fieldCount; i++) {
		if (media->fields[i]->id == 162) {
            if (media->fields[i] == record->fields[11]) {
                this->imageIndex = i;
            }
			this->images[j++] = new Image(media->fields[i]);
		}
	}
}

void Scriptable::drawOn(cairo_t* cr) {
	this->images[this->imageIndex]->drawOn(cr);
}


Stage::Stage(ObjectRecord* record) : Scriptable(record) {
	this->stage = this;

	this->centerx = record->fields[0]->fields[2]->intValue() / 2;
	this->centery = record->fields[0]->fields[3]->intValue() / 2;

	ObjectRecord* sprites = record->fields[16];

	this->sprites = new Sprite*[sprites->fieldCount];

	this->spriteCount = sprites->fieldCount;

	for (uint32_t i = 0; i < sprites->fieldCount; i++) {
		this->sprites[i] = new Sprite(sprites->fields[i], this);
	}
}

void Stage::drawOn(cairo_t* cr) {
    cairo_save(cr);
    cairo_translate(cr, this->centerx, this->centery);
	Scriptable::drawOn(cr);

	for (uint32_t i = 0; i < this->spriteCount; i++) {
		this->sprites[i]->drawOn(cr);
	}
    cairo_restore(cr);
}

Sprite::Sprite(ObjectRecord* record, Stage* stage) : Scriptable(record) {
	this->stage = stage;

    this->x = record->fields[0]->fields[0]->doubleValue() - this->stage->centerx + this->images[this->imageIndex]->centerx;
    this->y = this->stage->centery - record->fields[0]->fields[1]->doubleValue() - this->images[this->imageIndex]->centery;

    this->rotation = record->fields[14]->doubleValue() * M_PI / 180.0;
}

void Sprite::drawOn(cairo_t* cr) {
    cairo_save(cr);

    cairo_translate(cr, this->x, -this->y);
    cairo_rotate(cr, this->rotation);
	Scriptable::drawOn(cr);

    cairo_restore(cr);
}


Media::Media(ObjectRecord* record) {
	this->name = record->fields[0]->data;
}


Image::Image(ObjectRecord* record) : Media(record) {
    if (record->fieldCount >= 6 && !record->fields[5]->isNull()) {
        this->form = new Form(record->fields[5]);
    } else {
        this->form = new Form(record->fields[1]);
    }
	this->centerx = record->fields[2]->fields[0]->intValue();
	this->centery = record->fields[2]->fields[1]->intValue();
}

void Image::drawOn(cairo_t* cr) {
    cairo_save(cr);
    cairo_translate(cr, -this->centerx, -this->centery);
	this->form->drawOn(cr);
    cairo_restore(cr);
}


Form::Form(ObjectRecord* record) {
	this->width = record->fields[0]->uintValue();
	this->height = record->fields[1]->uintValue();

	this->depth = record->fields[2]->uintValue();

	uint32_t* bitmap;
	if (record->fields[4]->id == 11) {
		bitmap = this->decompress((uint8_t*) record->fields[4]->data, record->fields[4]->dataSize);
	} else {
		bitmap = (uint32_t*) record->fields[4]->data;
	}

	if (record->fieldCount >= 6) {
        ObjectRecord* colors = record->fields[5];
        this->colors = new uint32_t[colors->fieldCount];
        for (uint32_t i = 0; i < colors->fieldCount; i++) {
            this->colors[i] = colors->fields[i]->colorValue();
        }
	}

	int32_t stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, this->width);

	bitmap = this->resizeBitmap(bitmap, cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, this->width));

	this->image = cairo_image_surface_create_for_data((uint8_t*) bitmap, CAIRO_FORMAT_ARGB32, this->width, this->height, stride);
}

uint32_t* Form::resizeBitmap(uint32_t* bitmap, uint32_t stride) {
	uint32_t* newBitmap = new uint32_t[stride * this->height];

    if (this->depth <= 8) {
        const uint32_t* colors = this->colors;
        if (colors == NULL) {
            colors = squeakColors;
        }

        uint32_t l = this->bitmapSize / this->height;
        uint32_t i = (1 << this->depth) - 1;
        uint32_t j = 32 / this->depth;
        for(uint32_t y = 0; y < this->height; y++) {
            for(uint32_t x = 0; x < this->width; x++) {
                newBitmap[y * this->width + x] = colors[(bitmap[y * l + (x - (x % j)) / j] / (1 << this->depth * (j - x % j - 1))) & i];
            }
        }
    }
    if (this->depth == 32) {
    	for (uint32_t i = 0; i < this->bitmapSize; i++) {
            newBitmap[i] = bitmap[i];
        }
    }

	return newBitmap;
}

uint32_t* Form::decompress(uint8_t* raw, uint32_t rawSize) {
	ByteStream* stream = new ByteStream(raw, rawSize);

	this->bitmapSize = this->decodeInt(stream);

	uint32_t* bitmap = new uint32_t[this->bitmapSize];

	uint32_t j = 0;

	while (j < this->bitmapSize) {
		uint32_t k = this->decodeInt(stream);
		uint32_t l = k >> 2;

		uint32_t tn;
		uint32_t ti;

		switch(k & 3) {
		case 0:
			j++;
			break;
		case 1:
			tn = stream->uint8();
			ti = (tn << 24) | (tn << 16) | (tn << 8) | tn;
			for (uint32_t j2 = 0; j2 < l; j2++) {
				bitmap[j++] = ti;
			}
			break;
		case 2:
			tn = stream->uint32();
			for (uint32_t j2 = 0; j2 < l; j2++) {
				bitmap[j++] = tn;
			}
			break;
		case 3:
			for (uint32_t j2 = 0; j2 < l; j2++) {
				bitmap[j++] = stream->uint32();
			}
			break;
		}
	}
	return bitmap;
}

uint32_t Form::decodeInt(ByteStream* stream) {
	uint8_t i = stream->uint8();
	if (i <= 223) {
		return i;
	} else if (i <= 254) {
		return (i - 224) << 8 | stream->uint8();
	}
	return stream->uint32();
}

void Form::drawOn(cairo_t* cr) {
	cairo_set_source_surface(cr, this->image, 0, 0);
	cairo_paint(cr);
}
