#include "Generator.h"
#include <algorithm>
#include <fstream>

double EPS = 0.000; // < Very funny

double constCuts(int countCuts){ // static
	return (countCuts + 1)* 0.1f;
}

bool Generator::isTrue(int probability) { // static
	int i = rand() % probability;
	if ((i % probability) == 1)
		return true;
	return false;
}


SRMap Generator::GenerateMap(int countCuts) { // static
	SRMap map;
	for (int i = 0; i < countCuts; i++)
	{
		if (isTrue(probMissed))
			continue;
		double r;
		bool isDup;
		do {
			isDup = false;
			r = constCuts(rand() % countCuts);
			for (unsigned int j = 0; j < map.cuts.size(); j++)
			{
				if (map.cuts[j] == r)
				{
					isDup = true;
				}
			}
		}while(isDup);
		if (isTrue(probError))
			r += EPS * (rand() % 100);
		map.cuts.push_back(r);
	}
	std::sort(map.cuts.begin(), map.cuts.end());
	for (unsigned int j = 0; j < map.cuts.size() - 1; j++)
	{
		map.difCuts.push_back(map.cuts[j + 1] - map.cuts[j]);
	}
	return map;
}


SetSRMaps * Generator::GenerateSetMap(int countMaps) { // static
	SetSRMaps * setMaps = new SetSRMaps;
	setMaps->countMaps = countMaps;

	for (int i = 0; i < countMaps; i++)
	{
		int countCuts = 1 + rand() % maxCountCuts;
		setMaps->maps.push_back(GenerateMap(countCuts));
	}
	return setMaps;
}

SetSRMaps * Generator::GenerateSetMap(char * filename) {
	SetSRMaps * setMaps = new SetSRMaps; // no need in heap allocation
	std::ifstream in(filename); // TODO: checks on invalid input
	int countMaps;
	in >> countMaps;

	for (int i = 0; i < countMaps; i++) {
		int countCuts;
		in >> countCuts;
		SRMap map;
		for (int i = 0; i < countCuts; i++) {
			double cut;
			in >> cut;
			map.cuts.push_back(cut);
		}
		for (unsigned int j = 0; j < map.cuts.size() - 1; j++) // for(auto j=1; j<maps.cuts.size(); ++j)
		{
			map.difCuts.push_back(map.cuts[j + 1] - map.cuts[j]); // maps.difCuts.push_back(map.cuts[j]-map.cuts[j-1]);
		}
		setMaps->maps.push_back(map);
	}

	in.close(); // Destructor of in should call that
	setMaps->countMaps = countMaps;
	return setMaps;
}
