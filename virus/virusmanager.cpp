#include "virusmanager.hpp"

namespace termd {

	VirusManager::VirusManager(Player& p) : player(p) {}

	VirusManager::~VirusManager() {
		purge_viruses();
		purge_dead_viruses();
	}

	void VirusManager::purge_viruses() {
		for (Virus* vir : viruses) {
			delete vir;
		}
		viruses.clear();
	}

	void VirusManager::purge_dead_viruses() {
		for (Virus* vir : dead_viruses) {
			delete vir;
		}
		dead_viruses.clear();
	}

	bool VirusManager::update() {
		if (viruses.empty()) {
			return false;
		}
		for (auto i = viruses.begin(); i != viruses.end(); ) {
			if((*i)->update() == false) {
				//If virus is flagging removal, remove it!
				dead_viruses.push_back(*i);
				player.modify_ram( (*i)->get_reward() );
				i = viruses.erase(i);
			}else if((*i)->destination_reached()){
				//Reached goal!
				player.take_damage(1);
				dead_viruses.push_back(*i);
				i = viruses.erase(i);
			}else{
				++i;
			}
		}
		return true;
	}

	void VirusManager::draw_viruses(GUI & gui) {
		for (auto i = viruses.begin(); i != viruses.end(); ++i) {
			if((*i)->draw(gui) == false) {
				//If tower failed to draw:
				#ifdef DEBUGGING
				#include <iostream>
				std::cout << "Failed to draw Virus! " << std::endl;
				#endif //DEBUGGING
			}
		}
	}

	void VirusManager::add_virus(Virus* vir) {
		//TODO switch case over ids and pushback correct virus to vector.
		viruses.push_back(vir);
	}

	void VirusManager::end_of_wave() {
		purge_dead_viruses();
		purge_viruses();
	}

	const std::vector<Virus*>& VirusManager::get_viruses() const {
		return viruses;
	}

}
