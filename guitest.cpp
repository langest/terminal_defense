#include "gui.hpp"
#include <iostream>

int main() {
	
	GUI g;
	getch();
	g.move_cursor_down();
	getch();
	g.move_cursor_right();
	getch();
	g.move_cursor_up();
	getch();
	g.move_cursor_left();
	getch();

	return 0;
}
