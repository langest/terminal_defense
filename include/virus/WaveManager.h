#pragma once

namespace termd {

class CVirusManager;
class CTowerManager;

class CWaveManager {
	public:
		CWaveManager(
				int boardRows,
				int boardCols,
				CVirusManager& virusManager,
				CTowerManager& towerManager
			);

		bool update();

	private:
		void trySpawn();

		CVirusManager& mVirusManager;
		CTowerManager& mTowerManager;
};
}
