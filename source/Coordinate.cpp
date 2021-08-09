#include <Coordinate.h>

namespace termd {

CCoordinate::CCoordinate()
    : mRow()
    , mCol() {}

CCoordinate::CCoordinate(int row, int col)
    : mRow(row)
    , mCol(col) {}

CCoordinate::CCoordinate(const CCoordinate& src)
    : mRow(src.mRow)
    , mCol(src.mCol) {}

CCoordinate& CCoordinate::operator=(const CCoordinate& src) {
    mCol = src.mCol;
    mRow = src.mRow;
    return *this;
}

bool CCoordinate::operator==(const CCoordinate& other) const {
    return other.mRow == mRow && other.mCol == mCol;
}

bool CCoordinate::operator!=(const CCoordinate& other) const {
    return other.mRow != mRow || other.mCol != mCol;
}

bool CCoordinate::operator<(const CCoordinate& other) const {
    if (mRow == other.mRow) {
        return mCol < other.mCol;
    }
    return mRow < other.mRow;
}

bool CCoordinate::operator>(const CCoordinate& other) const {
    if (mRow == other.mRow) {
        return mCol > other.mCol;
    }
    return mRow > other.mRow;
}

double CCoordinate::distance(const CCoordinate& other) const {
    return std::sqrt(
        (other.getRow() - mRow) * (other.getRow() - mRow) + (other.getCol() - mCol) * (other.getCol() - mCol));
}

int CCoordinate::getCol() const {
    return mCol;
}

void CCoordinate::addCol(int delta) {
    mCol += delta;
}

void CCoordinate::setCol(int col) {
    mCol = col;
}

int CCoordinate::getRow() const {
    return mRow;
}

void CCoordinate::addRow(int delta) {
    mRow += delta;
}

void CCoordinate::setRow(int row) {
    mRow = row;
}

std::ostream& operator<<(std::ostream& os, const CCoordinate& coord) {
    os << coord.getRow() << " " << coord.getCol();
    return os;
}

std::istream& operator>>(std::istream& is, CCoordinate& coord) {
    int r, c;
    is >> r;
    is >> c;
    coord.setRow(r);
    coord.setCol(c);
    return is;
}

CCoordinate CCoordinate::operator-(const CCoordinate& other) const {
    return CCoordinate(this->mRow - other.mRow, this->mCol - other.mCol);
}

CCoordinate CCoordinate::operator+(const CCoordinate& other) const {
    return CCoordinate(this->mRow + other.mRow, this->mCol + other.mCol);
}

void CCoordinate::operator-=(const CCoordinate& other) {
    mRow = mRow - other.mRow;
    mCol = mCol - other.mCol;
}

void CCoordinate::operator+=(const CCoordinate& other) {
    mRow = mRow + other.mRow;
    mCol = mCol + other.mCol;
}

double CCoordinate::length() const {
    return sqrt(mRow * mRow + mCol * mCol);
}

}
