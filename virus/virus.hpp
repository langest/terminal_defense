#ifndef termd_virus
#define termd_virus

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#ifndef termd_memory
#define termd_memory
#include <memory>
#endif //memory

#include "../gui.hpp"
#include "../coord.hpp"
#include "path.hpp"

namespace termd {
	//typedef virus_ptr below!
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
			Virus(int hp, int sta_inc, int rew, char fx);
			Virus(const Virus &);
			virtual ~Virus();

			Virus& operator=(const Virus &) = delete;

			virtual bool update(); //Make the monster behave
			bool draw() const; //Draw the beauty
			void move_to(Coord);

			int get_reward() const;
			Coord get_pos() const;
			bool destination_reached() const;
			void take_damage(int);
	};
	typedef std::unique_ptr<Virus> virus_ptr;
}

#endif //termd_virus
