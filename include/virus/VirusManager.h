#pragma once

#include <memory>
#include <vector>

#include <logging/Logger.h>
#include <virus/Virus.h>

namespace termd {

class CPlayer;

class CVirusManager {
	public:
		CVirusManager(CPlayer& player);

		bool update();
		void initInvasion(const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);
		void finishInvasion();

		const std::vector<std::unique_ptr<int>>& getViruses() const;

		void addVirus(std::unique_ptr<CVirus>&& virus);
		void drawViruses() const;

		bool hasNextWave() const;

	private:
		CPlayer& mPlayer;
		std::vector<std::unique_ptr<int>> mInts;
		std::vector<std::unique_ptr<CVirus>> mViruses;
		CLogger mLogger;
};

}
