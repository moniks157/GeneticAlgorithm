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

Member::~Member()
{
	cout << "I am dead " << endl;
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
	for (int i = 0; i < _length; i++) 
	{
		for (int j = 0; j < _length; j++)
		{
			int d = distanceMatrix[i][j];
			int f = flowMatrix[_genes[i] - 1][_genes[j] - 1];
			fitness += (f*d);
		}
	}
	_fitness = fitness;
}
