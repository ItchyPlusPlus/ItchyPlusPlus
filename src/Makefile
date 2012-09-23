objects = main.o scratchio.o scratchobjects.o
headers = scratchio.h scratchobjects.h

itchy: $(objects) 
	g++ -o $@ $(objects) -lcairo `sdl-config --cflags --libs`

$(objects): $(headers)