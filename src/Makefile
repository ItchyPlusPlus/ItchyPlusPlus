objects = main.o Scratch1.x/scratchio.o Scratch1.x/scratchobjects.o Scratch2.x/Reader.cpp
headers = Scratch1.x/scratchio.h Scratch1.x/scratchobjects.h
binary = itchy
INSTALL_PATH?=/usr/local
DESTDIR?=/

$(binary): $(objects) 
	g++ -o $@ $(objects) `pkg-config --cflags --libs cairo` `sdl-config --cflags --libs`

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)

.PHONY: install
install: $(binary)
	mkdir -p $(DESTDIR)/$(INSTALL_PATH)/bin
	cp $(binary) $(DESTDIR)/$(INSTALL_PATH)/bin
