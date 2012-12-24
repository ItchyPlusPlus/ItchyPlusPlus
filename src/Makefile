objects = main.o Itchy.o gui.o
headers = gui.h Itchy.h ui_MainWindows.h
binary = itchy
INSTALL_PATH?=/usr/local
DESTDIR?=/

$(binary): $(objects) 
	$(MAKE) -C scratchio
	g++ -o $@ $(objects) `pkg-config --cflags --libs cairo` `sdl-config --cflags --libs` scratchio/libscratchio.a -lQtCore -lQtGui

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)

.PHONY: install
install: $(binary)
	mkdir -p $(DESTDIR)/$(INSTALL_PATH)/bin
	cp $(binary) $(DESTDIR)/$(INSTALL_PATH)/bin
