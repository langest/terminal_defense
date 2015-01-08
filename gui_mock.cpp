#include "gui.hpp"

namespace termd {

	GUI::GUI() {
	}

	GUI::~GUI() {
	}

	bool GUI::move_cursor_up() const {
		return true;
	}

	bool GUI::move_cursor_down() const {
		return true;
	}

	bool GUI::move_cursor_left() const {
		return true;
	}

	bool GUI::move_cursor_right() const {
		return true;
	}

	Coord GUI::get_cursor_pos() const {
		return Coord(5,5);
	}

	//Puts a char at specified coord in the guis window.
	//Does not refresh
	//Returns true iff successful
	bool GUI::draw(const Coord & coord, const char ch) const {
		return true;
	}

	//Draws a gfx in board window
	//Does not refresh
	bool GUI::draw_gfx(const Coord & coord, const std::vector<std::vector<char> > & gfx) const {
		return true;
	}

	bool GUI::draw_gfx(const Coord & coord, const char gfx) const {
		return true;
	}

	void GUI::print_intel(std::string message) const {
	}

	void GUI::draw_board_frame() const {
	}

	void GUI::draw_intel_frame() const {
	}

	void GUI::clear_game() const {
	}

	void GUI::clear_intel() const {
	}

	void GUI::refresh() const {
	}

}
