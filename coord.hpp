#ifndef temd_coord
#define temd_coord

class Coord {
	private:
		int col, row;
	public:
		Coord(int, int);
		Coord(Coord const &);
		Coord(Coord const *);

		int get_col() const;
		int get_row() const;
		bool set_col(const int);
		bool set_row(const int);
};

#endif //temd_coord