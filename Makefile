ncurses_test: ncursestest.cpp
	g++ -g -Wall ncursestest.cpp -lncurses -o ncursestest.out

gui_test: guitest.cpp
	g++ -g -Wall guitest.cpp -lncurses -o ncursestest.out

clean:
	rm *.o *.out
