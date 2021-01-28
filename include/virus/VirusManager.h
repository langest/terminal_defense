#pragma once

#include <memory>
#include <vector>

#include <virus/Virus.h>

namespace termd {

class CPlayer;

class CVirusManager {
	public:
		CVirusManager(CPlayer&);

		bool updateAllViruses();
		void updateAllVirusesEndOfWave();

		const std::vector<std::unique_ptr<CVirus>>& getAllViruses() const;

		void addVirus(std::unique_ptr<CVirus>&& virus);
		void drawAllViruses() const;

		bool hasNextWave() const;

	private:
		CPlayer& mPlayer;
		std::vector<std::unique_ptr<CVirus>> mViruses;
};

}
