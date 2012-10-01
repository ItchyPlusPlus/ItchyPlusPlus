objects = main.o scratchio.o scratchobjects.o
headers = scratchio.h scratchobjects.h
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
