#ifndef termd_tower
#define termd_tower

#include <cstddef>
#include <vector>
#include <memory>

#include "../gui.hpp"
#include "../coord.hpp"
#include "towerbase.hpp"

namespace termd {

	class Tower {
		private:
			
		protected:
			//Variables:
			int id;	
			Coord pos;			//Top-left

			const int num_rows;
			const int num_cols;

			std::vector<std::vector<bool> > blocking; 	//Ground path blocking, children can change this
			std::vector<std::vector<char> > gfx;			//The high-tech 3D model! Children can change this

			int age; //Used when save/load, will run this many "end_of_wave" when load game
			int buy_cost;
			int sell_value;
			float sell_decrease;

			//Functions:
		public:
			Tower(Coord, tower_base);
			virtual ~Tower() = 0;

			//Implemented:
			bool draw() const;
			int get_sell_value() const;
			const std::vector<std::vector<bool> >& get_blocking() const;
			int get_size_rows() const;
			int get_size_cols() const;
			int get_age() const;
			int get_cost() const;
			int get_id() const;
			void set_pos(Coord);

			//Virtual:
			virtual bool end_of_wave();
			//Pure Virtual:
			virtual bool update() = 0;
	};

	typedef std::unique_ptr<Tower> tower_ptr;

}
#endif //termd_tower
