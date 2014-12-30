#include "virusmanager.hpp"

VirsuManager::~VirusManager() {
	purge_viruses();
	purge_dead_viruses();
}

void VirusManager::purge_viruses() {
	for (Virus* vir : viruses) {
		delete vir;
	}
}

void VirusManager::purge_dead_viruses() {
	for (Virus* vir : dead_viruses) {
		delete vir;
	}
}

bool VirusManager::update() {
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

bool VirusManager::draw(GUI &) {
	return false; //TODO
}

void VirusManager::add_virus(Virus* vir) {
	viruses.push_back(vir);
}
