maindeps = game.o \
           gui.o \
           menu.o \
           coord.o \
           player.o \
           virus/virusmanager.o \
           virus/virusloader.o \
           virus/path.o \
           virus/virus.o \
					 virus/wave/waveloader.o \
					 virus/wave/waveinfo.o \
           maps/gameboard.o \
           tower/towermanager.o \
           tower/towerloader.o \
           tower/tower.o \
           tower/basic_tower_1x1.o \
           tower/direction_tower_1x1.o \
           tower/wall_1x1.o \
           tower/projectiles/projectilemanager.o \
           tower/projectiles/projectileloader.o \
           tower/projectiles/homingprojectile.o \
           tower/projectiles/directionprojectile.o \
           tower/projectiles/projectile.o

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
	rm -f $(maindeps) gui_mock.o gui.o terminaldefense.out

clean_saves:
	rm -f *.save
