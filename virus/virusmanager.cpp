#include "virusmanager.hpp"

VirsuManager::~VirusManager() {
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

void VirusManager::update() {
	if (viruses.empty()) {
		return false;
	}
	for (auto i = viruses.begin(); i != viruses.end(); ) {
		if((*i)->update() == false) {
			//If virus is flagging removal, remove it!
			//delete i->second;
			dead_viruses.push_back(*i);
			i = viruses.erase(i);
		}else{
			//Check if viruses has reached goal and put them in dead_viruses if so
			++i;
		}
	}
	return true;
}

void VirusManager::draw(GUI &) {
	return false; //TODO
}

void VirusManager::add_virus(int virus_id) {
	//TODO switch case over ids and pushback correct virus to vector.
	//viruses.push_back(vir);
}
