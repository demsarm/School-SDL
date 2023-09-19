main: main.cpp
	g++ -o main main.cpp `sdl2-config --cflags --libs`