#pragma once

#include <iostream>
#include <cmath>

namespace termd {

class CCoordinate {
	public:
		CCoordinate(int row, int col);
		CCoordinate(const CCoordinate& src);

		CCoordinate& operator=(const CCoordinate &);
		bool operator==(const CCoordinate &) const;
		bool operator!=(const CCoordinate &) const;
		bool operator<(const CCoordinate &) const;
		bool operator>(const CCoordinate &) const;

		double distance(const CCoordinate&) const; //Euclidian distance
		int getCol() const;
		void addCol(int delta);
		void setCol(int col);
		int getRow() const;
		void addRow(int delta);
		void setRow(int row);
		CCoordinate operator-(const CCoordinate&) const;
		CCoordinate operator+(const CCoordinate&) const;
		void operator-=(const CCoordinate&);
		void operator+=(const CCoordinate&);
		double length() const;

	private:
		int mRow;
		int mCol;
};

std::ostream & operator<<(std::ostream &, const CCoordinate &);
std::istream & operator>>(std::istream &, CCoordinate &);

}
