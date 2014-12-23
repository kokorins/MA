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
	graph[0] = 0;
	strcat(graph, "digraph D{\n");
}

SmithWaterman::~SmithWaterman(void)
{
	strcat(graph, "}");
	std::ofstream fout;
	fout.open("SmithWaterman.txt");
	fout << graph;
	fout.close();
}

void SmithWaterman::addMapToGraph(SRMap f, int fi)
{
	int fsize = f.cuts.size();
	std::vector<double> fcuts = f.cuts;
	std::vector<double> difCuts = f.difCuts;

	char str1[128];
	sprintf(str1,"subgraph cluster_%i {\n\tnode [style=filled];\n", fi);
	strcat(graph, str1);
	for (int i = 0; i < fsize - 1; i++)
	{
		char str[512];
		sprintf(str, "\t\"%i, %i, %f\" -> \"%i, %i, %f\" [ label = %f] ;\n", fi, i, fcuts[i], fi, i + 1, fcuts[i + 1], difCuts[i]);
		strcat(graph, str);
	}
	char str2[128];
	sprintf(str2,"\tlabel = \"Map %i\";\n\tcolor=blue\n}\n", fi);
	strcat(graph, str2);
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
	int fsize = f.difCuts.size(), ssize = s.difCuts.size();
	std::vector<double> fcuts = f.cuts, scuts = s.cuts;
	std::vector<double> fdif = f.difCuts, sdif = s.difCuts;

	for (int i = 0; i < fsize; i++)
		t[i][ssize] = BONUS;
	for (int i = 0; i < ssize; i++)
		t[fsize][i] = BONUS;
	t[fsize][ssize] = BONUS;

	int imax = 0, jmax = 0;
	double max = MIN, difsum;
	for (int i = fsize - 1; i > -1; i--)
	{
		for (int j = ssize - 1; j > -1; j--)
		{
			double tmax = MIN;
			difsum = 0;
			for (int k = i + 1; k <= fsize; k++)
			{
				difsum += fdif[k - 1];
				double h = t[k][j + 1] + MISS * (k - i - 1) + penaltyMiss(fabs(difsum - sdif[j])) + BONUS;
				indexMax(tmax, h, backi[i][j], backj[i][j], k, j + 1);
			}

			difsum = 0;
			for (int k = j + 1; k <= ssize; k++)
			{
				difsum += sdif[k - 1];
				double h = t[i + 1][k] + MISS * (k - j - 1) + penaltyMiss(fabs(difsum - fdif[i])) + BONUS;
				indexMax(tmax, h, backi[i][j], backj[i][j], i + 1, k);
			}

			t[i][j] = tmax;
			indexMax(max, tmax, imax, jmax, i, j);
		}
	}
	int k = imax;
	int l = jmax;
	char str[128];
	do
	{
		sprintf(str, "\t\"%i, %i, %f\" -> \"%i, %i, %f\"[color=\"red\",dir=\"both\"];\n", fi, k, fcuts[k], si, l, scuts[l]);
		strcat(graph, str);

		k = backi[imax][jmax];
		l = backj[imax][jmax];
		imax = k;
		jmax = l;
	}while (imax != fsize && jmax != ssize);
	sprintf(str, "\t\"%i, %i, %f\" -> \"%i, %i, %f\"[color=\"red\",dir=\"both\"];\n", fi, k, fcuts[imax], si, l, scuts[jmax]);
	strcat(graph, str);
}