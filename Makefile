maindeps = game.o \
         menu.o \
         coord.o \
         player.o \
         virus/virusmanager.o \
         virus/path.o \
         virus/virus.o \
         maps/gameboard.o \
         tower/towermanager.o \
         tower/tower.o \
         tower/basic_tower_1x1.o \
         tower/right_tower_1x1.o \
         tower/wall_1x1.o \
         tower/projectiles/projectilemanager.o \
         tower/projectiles/homingprojectile.o \
         tower/projectiles/rightprojectile.o \
         tower/projectiles/projectile.o

maindepsheaders = $(maindeps:.o=.hpp)

CXXFLAGS = -lncurses \
           -g \
           -Wall \
           -std=c++11

all: gui_non_mock main.cpp $(maindeps) $(maindepsheaders)
	$(CXX) -o terminaldefense.out main.cpp $(CXXFLAGS) $(maindeps) gui.o

mock: gui_mock main.cpp $(maindeps) $(maindepsheaders)
	$(CXX) -o terminaldefense.out main.cpp $(CXXFLAGS) -DMOCK_GUI $(maindeps) gui_mock.o

gui_non_mock: gui.hpp gui.cpp
	$(CXX) -c gui.hpp gui.cpp $(CXXFLAGS)
gui_mock: gui.hpp gui_mock.cpp
	$(CXX) -c gui.hpp gui_mock.cpp $(CXXFLAGS) -DMOCK_GUI

ncurses_test: test/ncursestest.cpp
	$(CXX) -std=c++0x -g -Wall test/ncursestest.cpp -lncurses -o ncursestest.out

gui_test: test/guitest.cpp gui.hpp gui.cpp
	$(CXX) -std=c++0x -g -Wall test/guitest.cpp gui.hpp gui.cpp -lncurses -o guitest.out

clean:
	rm -f $(maindeps) gui_mock.o gui.o terminaldefense.out

clean_saves:
	rm -f *.save
