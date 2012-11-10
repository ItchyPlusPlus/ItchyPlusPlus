objects = main.o Itchy.o scratchio.o scratchobjects.o gui.o
headers = scratchio.h scratchobjects.h gui.h Itchy.h
binary = itchy
INSTALL_PATH?=/usr/local
DESTDIR?=/
MYLIBRARIES=-lcairo -lSDLmain -lSDL

$(binary): $(objects) 
	g++ -o $@ $(objects) $(MYLIBRARIES)

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)

.PHONY: install
install: $(binary)
	mkdir -p $(DESTDIR)/$(INSTALL_PATH)/bin
	cp $(binary) $(DESTDIR)/$(INSTALL_PATH)/bin
