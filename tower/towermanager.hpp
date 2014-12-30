#ifndef termd_tower_manager
#define termd_tower_manager

class TowerManager {
	private:
		std::map<Coord, Tower*> towers;
		std::vector<Virus*>& dead_towers;

		void purge_towers();
		void purge_dead_towers();
	public:
		~TowerManager();

		bool update();
		void add_virus(Tower*);
};

#endif
