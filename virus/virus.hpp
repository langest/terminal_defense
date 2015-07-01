#ifndef termd_virus
#define termd_virus

#include <vector>
#include <memory>

#include "path.hpp"
#include "../gui.hpp"
#include "../coord.hpp"

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
			Virus(const Virus &, Path);
			virtual ~Virus();

			Virus& operator=(const Virus &) = delete;

			virtual bool update(); //Make the monster behave
			bool draw() const; //Draw the beauty

			int get_reward() const;
			Coord get_pos() const;
			bool destination_reached() const;
			void take_damage(int);
	};
	typedef std::unique_ptr<Virus> virus_ptr;
}

#endif //termd_virus
