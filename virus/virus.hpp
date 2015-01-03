#ifndef termd_virus
#define termd_virus

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#include "../gui.hpp"
#include "../coord.hpp"
#include "path.hpp"

namespace termd {

	class Virus {
		protected:
			int max_hp;
			int cur_hp;
			int stamina; 			//current stammina
			int stamina_increment;	//Determines the speed of the virus
			int reward;				//Kill reward
			std::vector<std::vector<char> > gfx; //The high-tech 3D model! Children can change this
			Path path;

			bool step(); //Make the monster walk along its path, if it can...
		public:
			Virus(Coord);
			Virus(const Virus &) = delete;
			virtual ~Virus();

			Virus& operator=(const Virus &) = delete;

			virtual bool update(); //Make the monster behave
			bool draw(const GUI&) const; //Draw the beauty

			int get_reward() const;
			Coord get_pos() const;
			bool destination_reached() const;
			void take_damage(int);
	};

}

#endif //termd_virus
