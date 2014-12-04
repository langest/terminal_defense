maindeps = game.o \
			gui.o \
			coord.o \
			virus/path.o \
			virus/virus.o \
			tower/tower.o \
			tower/wall_1x1.o \
			tower/wall_3x3.o \
			maps/gameboard.o


maindepsheaders = $(maindeps:.o=.hpp)

CXXFLAGS = -lncurses \
					 -g \
					 -Wall \
					 -std=c++11

all: main.cpp $(maindeps) $(maindepsheaders)
	$(CXX) -o terminaldefense.out main.cpp $(CXXFLAGS) $(maindeps)

ncurses_test: test/ncursestest.cpp
	$(CXX) -std=c++0x -g -Wall test/ncursestest.cpp -lncurses -o ncursestest.out

gui_test: test/guitest.cpp gui.hpp gui.cpp
	$(CXX) -std=c++0x -g -Wall test/guitest.cpp gui.hpp gui.cpp -lncurses -o guitest.out

clean:
	rm -fr *.o *.out
