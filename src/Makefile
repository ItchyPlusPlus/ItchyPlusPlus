objects = main.o scratchio.o scratchobjects.o
headers = scratchio.h scratchobjects.h
binary = itchy

$(binary): $(objects) 
	g++ -o $@ $(objects) `pkg-config --cflags --libs cairo` `sdl-config --cflags --libs`

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)