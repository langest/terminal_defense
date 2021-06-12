#pragma once

#include <vector>
#include <string>

#include <Coordinate.h>

namespace termd {

class GUI {
	public:
		GUI() = delete;
		~GUI();
		GUI(const GUI&) = delete;
		GUI& operator=(const GUI&) = delete;

		static void moveCursor(const CCoordinate &);
		static void moveCursorUp(int rMin);
		static void moveCursorDown(int rMax);
		static void moveCursorLeft(int cMin);
		static void moveCursorRight(int cMax);
		static CCoordinate getCursorPosition();
		static int getInput();

		static void draw(const CCoordinate& position, const char ch);
		static void drawCharacters(const CCoordinate& position, const std::vector<std::vector<char>>& characters);

		// Print all menu items in vector and return an other vector with the
		// CCoordinates where the items were drawn
		static std::vector<CCoordinate> printMenuItems(const std::vector<std::string> &);
		static void printText(const CCoordinate& start, const char* message, int n);
		static void drawFrame(const CCoordinate& topLeft, const CCoordinate& bottomRight);
		static void clearScreen();
		static void clearRectangle(const CCoordinate& topLeft, const CCoordinate& bottomRight);
		static void refresh();
};

}
