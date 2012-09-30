#include "scratchobjects.h"

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

    cout << this->rotation << endl;
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
	this->form = new Form(record->fields[1]);
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

    cout << (int)this->depth << endl;

	uint32_t* bitmap;
	if (record->fields[4]->id == 11) {
		bitmap = this->decompress((uint8_t*) record->fields[4]->data, record->fields[4]->dataSize);
	} else {
		bitmap = (uint32_t*) record->fields[4]->data;
	}

	int32_t stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, this->width);

	bitmap = this->resizeBitmap(bitmap, cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, this->width));

	this->image = cairo_image_surface_create_for_data((uint8_t*) bitmap, CAIRO_FORMAT_ARGB32, this->width, this->height, stride);

	//cout << cairo_status_to_string(cairo_surface_status(this->image)) << endl;
}

uint32_t* Form::resizeBitmap(uint32_t* bitmap, uint32_t stride) {
	uint32_t* newBitmap = new uint32_t[stride * this->height];

	for (uint32_t i = 0; i < this->bitmapSize; i++) {
		newBitmap[i] = bitmap[i];
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
		return (i - 224) * 256 + stream->uint8();
	}
	return stream->uint32();
}

void Form::drawOn(cairo_t* cr) {
	cairo_set_source_surface(cr, this->image, 0, 0);
	cairo_paint(cr);
}
