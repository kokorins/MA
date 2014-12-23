#ifndef SRMAP_H
#define SRMAP_H

#include <vector>

class SRMap
{
public:
	SRMap(void){};
	~SRMap(void){};

	std::vector<double> cuts;
	std::vector<double> difCuts;
};

#endif