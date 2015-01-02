#ifndef termd_virus_manager
#define termd_virus_manager

#include "../player.hpp"
#include "virus.hpp"

class VirusManager {
	private:
		Player& player;

		std::vector<Virus*> viruses;
		std::vector<Virus*> dead_viruses;

		void purge_viruses();
		void purge_dead_viruses();
	public:
		VirusManager(Player&);
		~VirusManager();

		bool update();
		void draw_viruses(GUI &);
		void add_virus(Virus*);
};

#endif
