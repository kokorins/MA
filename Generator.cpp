#include "Generator.h"
#include <algorithm>
#include <fstream>

double constCuts(int countCuts){
	return (countCuts + 1)* 0.1f;
}

bool Generator::isTrue(const double probability) const {
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(probability);
	return distribution(generator);
}


SRMap Generator::GenerateMap(int countCuts) const {
	SRMap map;
	for (int i = 0; i < countCuts; i++)
	{
		if (isTrue(constants::probMissed))
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
		if (isTrue(constants::probError))
			r += constants::EPS * (rand() % 100);
		map.cuts.push_back(r);
	}
	std::sort(map.cuts.begin(), map.cuts.end());
	for (unsigned int j = 0; j < map.cuts.size() - 1; j++)
	{
		map.frags.push_back(map.cuts[j + 1] - map.cuts[j]);
	}
	return map;
}


SetSRMaps * Generator::GenerateSetMap(int countMaps) const{
	SetSRMaps * setMaps = new SetSRMaps;
	setMaps->countMaps = countMaps;

	for (int i = 0; i < countMaps; i++)
	{
		int countCuts = 1 + rand() % constants::maxCountCuts;
		setMaps->maps.push_back(GenerateMap(countCuts));
	}
	return setMaps;
}

SetSRMaps * Generator::GenerateSetMap(const char * filename) {
	SetSRMaps * setMaps = new SetSRMaps;
	std::ifstream in(filename);
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
		for (unsigned int j = 0; j < map.cuts.size() - 1; j++)
		{
			map.frags.push_back(map.cuts[j + 1] - map.cuts[j]);
		}
		setMaps->maps.push_back(map);
	}

	in.close();
	setMaps->countMaps = countMaps;
	return setMaps;
}
