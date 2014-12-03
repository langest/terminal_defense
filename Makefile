maindeps = game.o \
			gui.o \
			coord.o \
			maps/gameboard.o \
			tower/tower.o \
			tower/wall_1x1.o

maindepsheaders = $(maindeps:.o=.hpp)

CXXFLAGS = -lncurses \
					 -g \
					 -Wall \
					 -std=c++11

all: main.cpp $(maindeps) $(maindepsheaders)
	$(CXX) -o terminaldefense.out main.cpp $(CXXFLAGS) $(maindeps)

ncurses_test: ncursestest.cpp
	$(CXX) -std=c++0x -g -Wall ncursestest.cpp -lncurses -o ncursestest.out

gui_test: guitest.cpp gui.hpp gui.cpp
	$(CXX) -std=c++0x -g -Wall guitest.cpp gui.hpp gui.cpp -lncurses -o guitest.out

clean:
	rm -fr *.o *.out
