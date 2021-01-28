#pragma once

namespace termd {

class CPlayer {
	public:
		CPlayer(int maxRam, int maxControlPoints);

		bool isAlive() const;
		int getRam() const;
		int getControlPoints() const;
		void modifyControlPoints(int delta);
		void modifyRam(int delta);

	private:
		int mRam;
		int mRamMax;
		int mControlPoints;
		int mControlPointsMax;
};

}
