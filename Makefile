ncurses_test: ncursestest.cpp
	g++  -g  -Wall ncursestest.cpp -lncurses -o ncursestest.out

clean:
	rm *.o *.out
