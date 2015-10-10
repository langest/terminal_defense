#ifndef termd_definitions
#define termd_definitions

#include <limits>

namespace termd {

//Framerate, number of frames / 1000ms
const int Frames = 30;

//Wave spawnrate
const int SpawnRate = 45;

//Typically needed numbers
const double PI = 3.1415;
const int IntMax = std::numeric_limits<int>::max();
const int IntMin = std::numeric_limits<int>::min();

//Virus default stepcosts
const int VirusStepCost = 1000;
const int VirusStepCostDiagonal = 1414;

//Projectile default stepcost
const int ProjStepCost = 1000;
const int ProjStepCostDiagonal = 1414;

//Player info
const int PlayerDefaultHP = 3;
const int PlayerDefaultRAM = 10000;

//Map information
const int BoardR0 = 1;
const int BoardC0 = 1;
const int IntelCols = 50;
const int IntelRows = 2;
const int WindowSpace = 1;

//Buildings TODO make into enum class
const int Homing = 0;
const int Direction = 1;
const int TowerWall = 2;

//Tile info

}

#endif //termd_definitions
