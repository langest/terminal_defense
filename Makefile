all: main.cpp
	 g++  -g  -Wall  -lncurses main.cpp -o main.out


clean:
	rm *.o *.out
