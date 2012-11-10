objects = scratchio.o scratchobjects.o
sources = scratchio.cpp scratchobjects.cpp
headers = scratchio.h scratchobjects.h
static = libscratchio.a
INSTALL_PATH?=/usr/local
DESTDIR?=/

lib: $(objects)
	ar rcs $(static) $(objects)

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(static)

.PHONY: install
install: $(binary)
	mkdir -p $(DESTDIR)/$(INSTALL_PATH)/bin
	cp $(binary) $(DESTDIR)/$(INSTALL_PATH)/bin
