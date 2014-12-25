#include "SetSRMaps.h"
#include "SmithWaterman.h"
#include "Generator.h"

#include <cstdio>
#include <cstdlib>

#include <memory>
#include <iostream>

int main(void)
{
  std::unique_ptr<SetSRMaps> set(Generator::GenerateSetMap("H:/code/ma/input.txt"));
	SmithWaterman sw;

	//Smith Waterman
  for (int i = 0; i < set->maps.size(); i++)
		sw.addMapToGraph(set->maps[i], i);
  for (int i = 0; i < set->maps.size(); i++) {
    for (int j = 0; j < i; j++) {
			sw.align(set->maps[i], set->maps[j], i, j);
		}
	}
  std::cout<<sw.getDot();
	return 0;
}
