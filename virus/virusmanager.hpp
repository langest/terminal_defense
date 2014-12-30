#ifndef termd_virus_manager
#define termd_virus_manager

#include "virus.hpp"

class VirusManager {
	private:
		//TODO, change to a player class reference with logic to check if dead etc.
		int & ram;			//Player money
		int & player_hp;	//Player hp

		std::vector<Virus*> viruses;
		std::vector<Virus*> dead_viruses;

		void purge_viruses();
		void purge_dead_viruses();
	public:
		VirusManager(int&, int&);
		~VirusManager();

		bool update();
		void draw_viruses(GUI &);
		void add_virus(Virus*);
};

#endif
