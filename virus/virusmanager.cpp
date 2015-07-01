#include "virusmanager.hpp"

namespace termd {

	VirusManager::VirusManager(Player& p) : player(p) {}

	VirusManager::~VirusManager() {
		viruses.clear();
		dead_viruses.clear();
	}

	bool VirusManager::update() {
		if (viruses.empty()) {
			return false;
		}
		for (auto i = viruses.begin(); i != viruses.end(); ) {
			if((*i)->update() == false) {
				//If virus is flagging removal, remove it!
				player.modify_ram( (*i)->get_reward() );
				dead_viruses.push_back(std::move(*i));
				i = viruses.erase(i);
			}else if((*i)->destination_reached()){
				//Reached goal!
				player.take_damage(1);
				dead_viruses.push_back(std::move(*i));
				i = viruses.erase(i);
			}else{
				++i;
			}
		}
		return true;
	}

	void VirusManager::draw_viruses() const {
		for (auto i = viruses.begin(); i != viruses.end(); ++i) {
			if((*i)->draw() == false) {
				//TODO debugging
			}
		}
	}

	void VirusManager::add_virus(virus_ptr vir) {
		//TODO switch case over ids and pushback correct virus to vector.
		viruses.push_back(std::move(vir));
	}

	void VirusManager::end_of_wave() {
		dead_viruses.clear();
		viruses.clear();
	}

	const std::vector<virus_ptr>& VirusManager::get_viruses() const {
		return viruses;
	}

}
