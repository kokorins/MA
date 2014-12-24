#ifndef GENERATE_H
#define GENERATE_H

#include "SRMap.h"
#include "SetSRMaps.h"

//TODO: wrap in struct v
const int probMissed = 100;
const int countCuts = 100;
const int defCountCuts = 20;
const int probError = 2;
const int maxCountCuts = 10;
//^

/**
 * Add consts to all functions if they dont modify code
 */
class Generator
{
public:
	SRMap GenerateMap(int countCuts);
	SetSRMaps * GenerateSetMap(int countMaps); // why bare pointer?
	SetSRMaps * GenerateSetMap(char * filename); // why bare pointer and bare non const pointer on arg?
	bool isTrue(int probability); //TODO: < generalize function
};

#endif
