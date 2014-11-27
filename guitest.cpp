#include "gui.hpp"
#include <iostream>

int main() {
	
	GUI g;
	std::cout << g.move_cursor_down();
	getch();
	std::cout << g.move_cursor_down();
	std::cout << g.move_cursor_down();
	std::cout << g.move_cursor_down();
	g.move_cursor_down();
	getch();

	return 0;
}
