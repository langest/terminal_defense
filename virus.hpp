#ifndef termd_virus
#define termd_virus

class Virus {
	private:
		int max_hp
		int cur_hp;
		int stamina; //Determines the speed of the virus
		char gfx;
		Path path;

		bool pathfind(); //Find a path through them maze wich it can follow
		bool step(); //Make the monster walk along its path
	public:
		bool update(); //Make the mosnster behave
};

#endif //termd_virus
