#ifndef SRMAP_H
#define SRMAP_H

#include <vector>

class SRMap // struct?
{
public:
	SRMap(void){}; // hmm
	~SRMap(void){}; // hmm

	std::vector<double> cuts;
	std::vector<double> difCuts;
};
/**
 struct SRMap {
 	std::vector<double> cuts;
 	std::vector<double> frags;
 }
 */

#endif
