class Coord {
	private:
		int col, row;
	public:
		int get_col() const;
		int get_row() const;
		bool set_col(const int &);
		bool set_row(const int &);
};
