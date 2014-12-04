#ifndef termd_virus
#define termd_virus

#ifndef termd_vector
#define termd_vector
#include <vector>
#endif //termd_vector

#include "../gui.hpp"
#include "../coord.hpp"

class Virus {
	protected:
		int max_hp
		int cur_hp;
		int stamina_increment;
		int stamina; //Determines the speed of the virus
		std::vector<std::vector<char> > gfx; //The high-tech 3D model! Children can change this
		Path path;

		bool pathfind(); //Find a path through them maze wich it can follow
		bool step(); //Make the monster walk along its path
	public:
		Virus();
		Virus(const Virus &);
		~Virus():

		operator=(const Virus &);

		virtual bool update(); //Make the monster behave
		bool draw(GUI&); //Draw the beauty

		Coord get_pos();
};

#endif //termd_virus
