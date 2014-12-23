#include "SetSRMaps.h"
#include "SmithWaterman.h"
#include "Generator.h"
#include <cstdio>
#include <cstdlib>

int main(void)
{
	int countMaps = 2;
	//Create maps
	Generator gen;
	//SetSRMaps * set = gen.GenerateSetMap(countMaps);
	SetSRMaps * set = gen.GenerateSetMap("input.txt");
	SmithWaterman sw;

	//Smith–Waterman
	for (int i = 0; i < countMaps; i++)
	{
		sw.addMapToGraph(set->maps[i], i);
	}
	for (int i = 0; i < countMaps; i++)
	{
		for (int j = 0; j < i; j++)
		{
			sw.align(set->maps[i], set->maps[j], i, j);
		}
	}
	delete set;
	return 0;
}