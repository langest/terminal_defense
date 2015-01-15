#ifndef termd_virus_manager
#define termd_virus_manager

#include "../player.hpp"
#include "virus.hpp"

namespace termd {

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
			void draw_viruses() const;
			void add_virus(Virus*);
			void end_of_wave();
			const std::vector<Virus*>& get_viruses() const;
	};

}

#endif
