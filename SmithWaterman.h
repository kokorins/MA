#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "SRMap.h"
//#include "map.h"

const int MAX_CUTS = 32;
const double BONUS = 0.3;
const double MISS = -0.1;

const double MIN = -10000;

class SmithWaterman
{
public:
	SmithWaterman();
	~SmithWaterman(void);
	
	void addMapToGraph(SRMap f, int fi);
	void align(SRMap f, SRMap s, int fi, int si);

private:
	double t[MAX_CUTS][MAX_CUTS];
	int backi[MAX_CUTS][MAX_CUTS];
	int backj[MAX_CUTS][MAX_CUTS];
	int numVertex;
	char graph[100000];
	double penaltyMiss(double miss);
};

#endif