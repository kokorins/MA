#ifndef GENERATE_H
#define GENERATE_H

#include "SRMap.h"
#include "SetSRMaps.h"

const int probMissed = 100;
const int countCuts = 100;
const int defCountCuts = 20;
const int probError = 2;
const int maxCountCuts = 10;

class Generator
{
public:
	SRMap GenerateMap(int countCuts);
	SetSRMaps * GenerateSetMap(int countMaps);
	SetSRMaps * GenerateSetMap(char * filename);
	bool isTrue(int probability);
};

#endif