#include "stdafx.h"
#include "Algorithm.h"
#include <algorithm> 

Algorithm::Algorithm(int amount, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	_amount = amount;
	_hadXX = hadXX;
	_distanceMatrix = distanceMatrix;
	_flowMatrix = flowMatrix;
	for (int i = 0; i < amount; i++) {
		vector<int> _genes;
		for (int i = 1; i <= hadXX; i++) {
			_genes.push_back(i);
		}
		random_shuffle(_genes.begin(), _genes.end());
		_members.push_back(_genes);
	}
}


Algorithm::~Algorithm()
{
}

void Algorithm::setFitness(int index)
{
	int fitness = 0;
	vector<int> _genes = _members[index];
	for (int i = 0; i < _hadXX; i++)
	{
		for (int j = 0; j < _hadXX; j++)
		{
			int d = _distanceMatrix[i][j];
			int f = _flowMatrix[_genes[i] - 1][_genes[j] - 1];
			fitness += (f*d);
		}
	}
	_fitness.push_back(fitness);
}
