#pragma once

#include <functional>
#include <memory>
#include <set>
#include <vector>

#include <logging/Logger.h>
#include <virus/Virus.h>

namespace termd {

class CPlayer;

class CVirusManager {
	public:
		typedef std::function<void(const CCoordinate& position, char graphic)> TDrawCall;

		CVirusManager(CPlayer& player, TDrawCall drawCall);

		bool update();
		void initInvasion(const std::set<CCoordinate>& startPositions, const std::set<CCoordinate>& endPositions, const std::map<CCoordinate, std::unique_ptr<ITower>>& towers);
		void finishInvasion();

		const std::vector<std::unique_ptr<CVirus>>& getViruses() const;

		void addVirus(std::unique_ptr<CVirus>&& virus);
		void drawViruses() const;

		bool hasNextWave() const;

	private:
		CPlayer& mPlayer;
		std::vector<std::unique_ptr<CVirus>> mViruses;
		TDrawCall mDrawCall;
		CLogger mLogger;
};

}
