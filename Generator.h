#ifndef GENERATE_H
#define GENERATE_H

#include "SRMap.h"
#include "SetSRMaps.h"
#include "Utils.h"
#include <random>

class Generator
{
public:
	SRMap GenerateMap(const int countCuts) const;
	SetSRMaps * GenerateSetMap(const int countMaps) const; // why bare pointer?
	SetSRMaps * GenerateSetMap(const char * filename) const; // why bare pointer
	bool isTrue(const double probability) const;
};

#endif
