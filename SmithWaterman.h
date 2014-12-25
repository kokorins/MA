#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "SRMap.h"
#include "Utils.h"
#include <sstream>

class SmithWaterman
{
public:
	SmithWaterman();
  ~SmithWaterman(void); // Throwable destructor
	
	void addMapToGraph(SRMap f, int fi);
	void align(SRMap f, SRMap s, int fi, int si);
	static double penaltyMiss(double miss);
  std::string getDot()const;
private:
	double t[constants::MAX_CUTS][constants::MAX_CUTS];
	int backi[constants::MAX_CUTS][constants::MAX_CUTS];
	int backj[constants::MAX_CUTS][constants::MAX_CUTS];
	int numVertex;
	std::stringstream ss;
	
};

#endif
