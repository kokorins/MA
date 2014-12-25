#ifndef GENERATE_H
#define GENERATE_H

#include "SRMap.h"
#include "SetSRMaps.h"
#include "Utils.h"

#include <random>

class Generator {
public:
	SRMap GenerateMap(const int countCuts) const;
  SetSRMaps * GenerateSetMap(const int countMaps) const; //TODO: why bare pointer?
  static SetSRMaps * GenerateSetMap(const char * filename); //TODO: why bare pointer
	bool isTrue(const double probability) const;
};

#endif
