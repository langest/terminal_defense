ncurses_test: ncursestest.cpp
	 g++  -g  -Wall  -lncurses ncursestest.cpp -o ncursestest.out


clean:
	rm *.o *.out
