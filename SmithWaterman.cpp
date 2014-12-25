#define _CRT_SECURE_NO_WARNINGS

#include "SmithWaterman.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

int max(int a, int b)
{
	if (a >= b)
		return a;
	return b;
}

int max3(int a, int b, int c)
{
	return max(max(a,b), c);
}

SmithWaterman::SmithWaterman()
{
	ss << "digraph D{\n";
}

SmithWaterman::~SmithWaterman(void)
{
	ss << "}";
	std::ofstream fout;
	fout.open("SmithWaterman.txt");
	fout << ss.str();
	fout.close();
}

void SmithWaterman::addMapToGraph(SRMap f, int fi)
{
	int fsize = f.cuts.size();
	std::vector<double> fcuts = f.cuts;
	std::vector<double> frags = f.frags;

	ss << "subgraph cluster_" << fi <<" {\n\tnode [style=filled];\n";
	for (int i = 0; i < fsize - 1; i++)
	{
		ss << "\t\"" << fi << ", " << i << ", " << fcuts[i] << "\" -> \"" << fi << ", " << i + 1 << ", " << fcuts[i + 1] << "\" [ label = " << frags[i] << "] ;\n";
	}
	ss << "\tlabel = \"Map " << fi << "\";\n\tcolor=blue\n}\n";
}

void p(double *f, int l)
{
	printf("T: ");
	for (int i = 0; i < l; i++)
		printf("%f ", f[i]);
	printf("\n");
}

double SmithWaterman::penaltyMiss(double miss)
{
  return -miss;
}

std::string SmithWaterman::getDot() const
{
  return ss.str();
}

void indexMax(double &max, double tmax, int &imax, int &jmax, int i, int j)
{
	if (tmax >= max)
	{
		imax = i;
		jmax = j;
		max = tmax;
	}
}

void SmithWaterman::align(SRMap f, SRMap s, int fi, int si)
{
	int fsize = f.frags.size(), ssize = s.frags.size();
	std::vector<double> fcuts = f.cuts, scuts = s.cuts;
  std::vector<double> fFrags = f.frags, sFrags = s.frags;

	for (int i = 0; i < fsize; i++)
		t[i][ssize] = constants::BONUS;
	for (int i = 0; i < ssize; i++)
		t[fsize][i] = constants::BONUS;
	t[fsize][ssize] = constants::BONUS;

	int imax = 0, jmax = 0;
	double max = constants::MIN, difsum;
	for (int i = fsize - 1; i > -1; i--)
	{
		for (int j = ssize - 1; j > -1; j--)
		{
			double tmax = constants::MIN;
			difsum = 0;
			for (int k = i + 1; k <= fsize; k++)
			{
        difsum += fFrags[k - 1];
        double h = t[k][j + 1] + constants::MISS * (k - i - 1) + penaltyMiss(fabs(difsum - sFrags[j])) + constants::BONUS;
				indexMax(tmax, h, backi[i][j], backj[i][j], k, j + 1);
			}

			difsum = 0;
			for (int k = j + 1; k <= ssize; k++)
			{
        difsum += sFrags[k - 1];
        double h = t[i + 1][k] + constants::MISS * (k - j - 1) + penaltyMiss(fabs(difsum - fFrags[i])) + constants::BONUS;
				indexMax(tmax, h, backi[i][j], backj[i][j], i + 1, k);
			}

			t[i][j] = tmax;
			indexMax(max, tmax, imax, jmax, i, j);
		}
	}
	int k = imax;
	int l = jmax;

	do
	{
		ss << "\t\"" << fi << ", " << k << ", " << fcuts[k] << "\" -> \"" << si << ", " << l << ", " << scuts[l] << "\"[color=\"red\",dir=\"both\"];\n";

		k = backi[imax][jmax];
		l = backj[imax][jmax];
		imax = k;
		jmax = l;
	}while (imax != fsize && jmax != ssize);
	ss << "\t\"" << fi << ", " << k << ", " << fcuts[imax] << "\" -> \"" << si << ", " << l << ", " << scuts[jmax] << "\"[color=\"red\",dir=\"both\"];\n";

}
