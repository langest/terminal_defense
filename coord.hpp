#ifndef termd_coord
#define termd_coord

#ifndef termd_iostream
#define termd_iostream
#include <iostream>
#endif

#ifndef termd_math
#define termd_math
#include <cmath>
#endif

namespace termd {

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

			double distance(const Coord&) const; //Euclidian distance
			int get_col() const;
			void add_col(int);
			bool set_col(const int);
			int get_row() const;
			void add_row(int);
			bool set_row(const int);
			Coord operator-(const Coord&) const;
			Coord operator+(const Coord&) const;
			void operator-=(const Coord&);
			void operator+=(const Coord&);
			double length() const;
	};

	std::ostream & operator<<(std::ostream &, const Coord &);
	std::istream & operator>>(std::istream &, Coord &);

}

#endif //termd_coord
