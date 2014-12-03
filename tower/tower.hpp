#ifndef termd_tower
#define termd_tower

#include "../gui.hpp"
#include "../coord.hpp"

#ifndef termd_cstddef
#define termd_cstddef
#include <cstddef>
#endif

template <size_t row_size = 1, size_t col_size = 1>
class Tower {
	private:
		
	protected:
		//Variables:
		Coord pos;			//Top-left

		bool** blocking; 	//Ground path blocking, children can change this
		char** gfx;			//The high-tech 3D model! Children can change this

		int sell_value;
		float sell_decrease;

		//Functions:
	public:
		Tower();
		template <size_t a, size_t b>
		Tower(const Tower<a, b> &);
		~Tower();

		Tower<row_size, col_size>& operator=(const Tower<row_size, col_size> &);

		//Implemented:
		bool draw(GUI &);
		const int get_sell_value() const;
		const bool get_blocking() const;
		int get_size_rows() const;
		int get_size_cols() const;

		//Virtual:
		virtual bool update() = 0;
		//virtual bool end_of_wave_update() = 0;
};

#endif //termd_tower
