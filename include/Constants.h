#pragma once

namespace termd {
//TODO remove constants file

const char* const Version = "0.X";

//Framerate, number of frames / 1000ms
const int Frames = 30;

//Wave spawnrate
const int SpawnRate = 45;

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
const int IntelCols = 50;
const int IntelRows = 2;
const int WindowSpace = 1;
}
