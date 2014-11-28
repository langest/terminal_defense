#ifndef temd_coord
#define temd_coord

class Coord {
	private:
		int col, row;
	public:
		Coord();
		Coord(int, int);
		Coord(const Coord &);
		Coord(const Coord *);

		Coord& operator=(const Coord &);
		bool operator==(const Coord &) const;
		bool operator!=(const Coord &) const;

		int get_col() const;
		int get_row() const;
		bool set_col(const int);
		bool set_row(const int);
};

#endif //temd_coord
