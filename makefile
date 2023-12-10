CXX = g++
COMFLAGS = -std=c++17 -Wall
LIBS = -lSDL2 -lSDL2_image

SRCS = main.cpp GameObject.cpp Player.cpp Vectors.cpp
OBJS = $(SRCS:.cpp=.o)

final: $(OBJS)
	$(CXX) -o main $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(COMFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -f $(OBJS)
