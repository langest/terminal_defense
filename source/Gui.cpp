#include <Gui.h>

#include <algorithm>
#include <ncurses.h>

#include <Version.h>

namespace termd {

void GUI::moveCursor(const CCoordinate& pos)
{
    int maxCol;
    int maxRow;
    getmaxyx(stdscr, maxRow, maxCol);

    const int toRow = pos.getRow();
    const int toCol = pos.getCol();

    if (toRow >= maxRow || toRow < 0) {
        return;
    }
    if (toCol >= maxCol || toCol < 0) {
        return;
    }
    move(pos.getRow(), pos.getCol());
}

void GUI::moveCursorUp(int rMin)
{
    int row;
    int col;
    getyx(stdscr, row, col);

    if (row <= rMin) {
        move(rMin, col);
        return;
    }

    move(row - 1, col);
}

void GUI::moveCursorDown(int rMax)
{
    int row;
    int col;
    getyx(stdscr, row, col);

    if (row >= rMax) {
        move(rMax, col);
        return;
    }

    move(row + 1, col);
}

void GUI::moveCursorLeft(int cMin)
{
    int row;
    int col;
    getyx(stdscr, row, col);

    if (col <= cMin) {
        move(row, cMin);
        return;
    }

    move(row, col - 1);
}

void GUI::moveCursorRight(int cMax)
{
    int row;
    int col;
    getyx(stdscr, row, col);

    if (col >= cMax) {
        move(row, cMax);
        return;
    }

    move(row, col + 1);
}

CCoordinate GUI::getCursorPosition()
{
    int row;
    int col;
    getyx(stdscr, row, col);
    return CCoordinate(row, col);
}

int GUI::getInput()
{
    return getch();
}

void GUI::draw(const CCoordinate& position, const char ch)
{
    int maxRow;
    int maxCol;
    getmaxyx(stdscr, maxRow, maxCol);

    const int drawRow = position.getRow();
    if (drawRow >= maxRow || drawRow < 0) {
        return;
    }

    const int drawCol = position.getCol();
    if (drawCol >= maxCol || drawCol < 0) {
        return;
    }

    int row;
    int col;
    getyx(stdscr, row, col);

    mvwaddch(stdscr, drawRow, drawCol, ch);
    move(row, col);
}

void GUI::drawCharacters(const CCoordinate& position, const std::vector<std::vector<char>>& characters)
{
    int maxRow;
    int maxCol;
    getmaxyx(stdscr, maxRow, maxCol);

    const int row = position.getRow();
    const int col = position.getCol();

    if ((int)characters.size() + row >= maxRow || row < 0) {
        return;
    }
    if ((int)characters[0].size() + col >= maxCol || col < 0) {
        return;
    }

    int curRow;
    int curCol;
    getyx(stdscr, curRow, curCol);

    for (unsigned int r = 0; r < characters.size(); ++r) {
        for (unsigned int c = 0; c < characters[0].size(); ++c) {
            mvaddch(position.getRow() + r, position.getCol() + c, characters[r][c]);
        }
    }

    move(curRow, curCol);
    return;
}

std::vector<CCoordinate> GUI::printMenuItems(const std::vector<std::string>& menuItems)
{
    std::vector<CCoordinate> itemCoordinates; // Return values, the position of the menu items
    if (menuItems.size() < 1) {
        return itemCoordinates;
    }

    int maxRow;
    int maxCol;
    getmaxyx(stdscr, maxRow, maxCol);

    size_t longestItem = 0; // Find the longest string
    for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
        longestItem = std::max(longestItem + 2, it->length()); // +2 because of menu markers
    }

    const int colPosition = maxCol / 2 - longestItem / 2;
    const int windowPiece = maxRow / 4;

    mvaddstr(windowPiece / 2, maxCol / 2 - 4, "* Menu *"); // Draw logo in first piece

    const int step = windowPiece * 2 / menuItems.size(); // step in the two middle pieces

    int itemPosition = windowPiece + step;
    for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
        std::string marker("> ");
        mvaddstr(itemPosition, colPosition, marker.append(*it).c_str()); // Draw the items in the middle pieces
        itemCoordinates.push_back(CCoordinate(itemPosition, colPosition));
        itemPosition += step;
    }

    const int bufferSize = 32;
    char version[bufferSize];
    snprintf(version, bufferSize, "Version: %s", GlobalVersionString.c_str());
    mvwaddstr(stdscr, windowPiece * 3 + windowPiece / 7 * 6, maxCol / 2, version); // Draw version in the end piece

    return itemCoordinates;
}

void GUI::printText(const CCoordinate& start, const char* message, int n)
{
    int curRow, curCol;
    getyx(stdscr, curRow, curCol);

    mvaddnstr(start.getRow(), start.getCol(), message, n);

    move(curRow, curCol);
}

void GUI::drawFrame(const CCoordinate& topLeft, const CCoordinate& bottomRight)
{
    int curRow;
    int curCol;
    getyx(stdscr, curRow, curCol);

    const int rMin = topLeft.getRow();
    const int cMin = topLeft.getCol();
    const int rMax = bottomRight.getRow();
    const int cMax = bottomRight.getCol();

    mvaddch(rMin, cMin, ACS_ULCORNER);
    mvaddch(rMax, cMin, ACS_LLCORNER);
    mvaddch(rMin, cMax, ACS_URCORNER);
    mvaddch(rMax, cMax, ACS_LRCORNER);

    mvhline(rMin, cMin + 1, ACS_HLINE, cMax - cMin - 1);
    mvvline(rMin + 1, cMin, ACS_VLINE, rMax - rMin - 1);
    mvhline(rMax, cMin + 1, ACS_HLINE, cMax - cMin - 1);
    mvvline(rMin + 1, cMax, ACS_VLINE, rMax - rMin - 1);

    move(curRow, curCol);
}

void GUI::clearScreen()
{
    int maxCol;
    int maxRow;
    getmaxyx(stdscr, maxRow, maxCol);

    GUI::clearRectangle(CCoordinate(0, 0), CCoordinate(maxCol, maxRow));
}

void GUI::clearRectangle(const CCoordinate& topLeft, const CCoordinate& bottomRight)
{
    int currentRow;
    int currentCol;
    getyx(stdscr, currentRow, currentCol);

    const int minRow = topLeft.getRow();
    const int minCol = topLeft.getCol();
    const int maxRow = bottomRight.getRow();
    const int maxCol = bottomRight.getRow();
    for (int r = minRow; r < maxRow; ++r) {
        move(r, 0);
        for (int c = minCol; c < maxCol; ++c) {
            addch(' ');
        }
    }

    move(currentRow, currentCol);
}

void GUI::refresh()
{
    wrefresh(stdscr);
}

}
