#ifndef termd_virus_manager
#define termd_virus_manager

#include "virus.hpp"
#include "../player.hpp"

namespace termd {

	class VirusManager {
		private:
			Player& player;

			std::vector<virus_ptr> viruses;
			std::vector<virus_ptr> dead_viruses;

			void purge_viruses();
			void purge_dead_viruses();
		public:
			VirusManager(Player&);
			~VirusManager();

			bool update();
			void draw_viruses() const;
			void add_virus(virus_ptr);
			void end_of_wave();
			const std::vector<virus_ptr>& get_viruses() const;
	};

}

#endif
