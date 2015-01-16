#ifndef termd_tower
#define termd_tower

#ifndef termd_cstddef
#define termd_cstddef
#include <cstddef>
#endif //term_cstddef

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#ifndef termd_memory
#define termd_memory
#include <memory>
#endif

#include "../gui.hpp"
#include "../coord.hpp"

namespace termd {
	typedef std::unique_ptr<Tower> tower_ptr;

	class Tower {
		private:
			
		protected:
			//Variables:
			Coord pos;			//Top-left

			std::vector<std::vector<bool> > blocking; 	//Ground path blocking, children can change this
			std::vector<std::vector<char> > gfx;			//The high-tech 3D model! Children can change this

			const int num_rows;
			const int num_cols;


			int age; //Used when save/load, will run this many "end_of_wave" when load game
			int sell_value;
			float sell_decrease;

			//Functions:
		public:
			Tower(Coord, int, int, int, float);
			virtual ~Tower() = 0;

			//Implemented:
			bool draw() const;
			int get_sell_value() const;
			const std::vector<std::vector<bool> >& get_blocking() const;
			int get_size_rows() const;
			int get_size_cols() const;
			int get_age() const;

			//Virtual:
			virtual bool end_of_wave();
			//Pure Virtual:
			virtual bool update() = 0;
			virtual int get_id() const = 0;
	};

}
#endif //termd_tower
