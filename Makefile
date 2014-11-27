ncurses_test: ncursestest.cpp
	g++ -std=c++0x -g -Wall ncursestest.cpp -lncurses -o ncursestest.out

gui_test: guitest.cpp gui.hpp gui.cpp
	g++ -std=c++0x -g -Wall guitest.cpp gui.hpp gui.cpp -lncurses -o guitest.out

clean:
	rm *.o *.out
