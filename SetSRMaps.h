#ifndef SETSRMAPS_H
#define SETSRMAPS_H

#include "SRMap.h"
#include <vector>

class SetSRMaps
{
public:
	SetSRMaps(void){};
	~SetSRMaps(void){};

	int countMaps;
	std::vector<SRMap> maps;
};

#endif