#pragma once

#include <cmath>
#include <iostream>

namespace termd {

class CCoordinate {
public:
    CCoordinate();
    CCoordinate(int row, int col);
    CCoordinate(const CCoordinate& src);

    CCoordinate& operator=(const CCoordinate& src);
    bool operator==(const CCoordinate& other) const;
    bool operator!=(const CCoordinate& other) const;
    bool operator<(const CCoordinate& other) const;
    bool operator>(const CCoordinate& other) const;

    double distance(const CCoordinate& other) const;
    double squaredDistance(const CCoordinate& other) const;
    int getCol() const;
    void addCol(int delta);
    void setCol(int col);
    int getRow() const;
    void addRow(int delta);
    void setRow(int row);
    CCoordinate operator-(const CCoordinate& other) const;
    CCoordinate operator+(const CCoordinate& other) const;
    void operator-=(const CCoordinate& other);
    void operator+=(const CCoordinate& other);
    double length() const;
    double squaredLength() const;
    double getAngle(const CCoordinate& other) const; // Radians

private:
    int mRow;
    int mCol;
};

std::ostream& operator<<(std::ostream&, const CCoordinate&);
std::istream& operator>>(std::istream&, CCoordinate&);

}
