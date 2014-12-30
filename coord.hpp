#ifndef termd_coord
#define termd_coord

#ifndef termd_iostream
#define termd_iostream
#include <iostream>
#endif

#ifndef termd_math
#define termd_math
#include <math.h>
#endif

class Coord {
	private:
		int row, col;
	public:
		Coord();
		Coord(int, int);
		Coord(const Coord &);
		Coord(const Coord *);

		Coord& operator=(const Coord &);
		bool operator==(const Coord &) const;
		bool operator!=(const Coord &) const;
		bool operator<(const Coord &) const;
		bool operator>(const Coord &) const;

		int get_col() const;
		int get_row() const;
		bool set_col(const int);
		bool set_row(const int);
		Coord operator-(const Coord&) const;
		Coord operator+(const Coord&) const;
		double length() const;
};

std::ostream & operator<<(std::ostream &, const Coord &);


#endif //termd_coord
