#include "stdafx.h"
#include "Member.h"
#include <iostream>


Member::Member(int length)
{
	_length = length;
	_fitness = 0;
	for (int i = 1; i <= length; i++) {
		_genes.push_back(i);
	}
	random_shuffle(_genes.begin(), _genes.end());
}

Member::Member(vector<int> genes)
{
	_length = genes.size();
	_genes = genes;
}

Member::Member(const Member & obj)
{
	cout << "Copy constructor allocating ptr." << endl;
	_length = obj._length;
	_genes = obj._genes;
	_fitness = obj._fitness;
}

Member::~Member()
{
}

void Member::print()
{
	for (int i = 0; i < _length; i++) {
		cout << _genes.at(i)<<" ";
	}
	cout << endl;
}

void Member::setFitness(vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	int fitness = 0;
	for (int i = 0; i < _genes.size(); i++)
	{
		for (int j = 0; j < _genes.size(); j++)
		{
			int d = distanceMatrix[i][j];
			int f = flowMatrix[_genes[i] - 1][_genes[j] - 1];
			fitness += (f*d);
		}
	}
	_fitness = fitness;
}

void Member::greedy(vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	int hadXX = distanceMatrix.size(); 
	int done = 1;
	vector<int> genome;
	vector<int> fitnesses;
	for (int i = 1; i <= hadXX; i++) {
		if (_genes[0] == i) {}
		else
		{
			genome.push_back(i);
		}
	}
	for (int j = 1; j < hadXX; j++)
	{
		for (int i = j; i < hadXX; i++)
		{
			if (_genes.size() == j)
			{
				_genes.push_back(genome[0]);
			}
			else
			{
				_genes[j] = genome[i - j];
			}
			setFitness(distanceMatrix, flowMatrix);
			fitnesses.push_back(_fitness);
		}
		vector<int> indexes;
		for (int i = 0; i <= fitnesses.size(); i++) {
			indexes.push_back(i);
		}
		
		for (int i = 0; i < genome.size(); i++)
		{
			for (int k = i; k < genome.size(); k++)
			{
				if (fitnesses[i] > fitnesses[k])
				{
					swap(fitnesses.at(i), fitnesses.at(k));
					swap(indexes[i], indexes[k]);
				}
			}
		}
		_genes[j] = genome[indexes[0]];
		genome.erase(genome.begin() + indexes[0]);
		fitnesses.clear();
		_length++;
	}
}


