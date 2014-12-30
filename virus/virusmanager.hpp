#ifndef termd_virus_manager
#define termd_virus_manager

#include "virus.hpp"

class VirusManager {
	private:
		std::vector<Virus*> viruses;
		std::vector<Virus*> dead_viruses;

		void purge_viruses();
		void purge_dead_viruses();
	public:
		~VirusManager();

		void update();
		void draw(GUI &);
		void add_virus(Virus*);
};

#endif
