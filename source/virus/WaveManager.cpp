#include <virus/WaveManager.h>

namespace termd {

CWaveManager::CWaveManager(int numRows, int numCols) :
	mNumRows(numRows),
	mNumCols(numCols) {}


void CWaveManager::initWave() {
	mUpdateCounter = 0;
}

}
