#include "stdafx.h"
#include "Population.h"
#include <ctime>
#include <iostream>
#include <string>
#include <map>
#include <random>


Population::Population(int amount, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	_amount = amount;
	_hadXX = hadXX;
	_distanceMatrix = distanceMatrix;
	_flowMatrix = flowMatrix;
	for (int i = 0; i < amount; i++) {
		Member* m = new Member(hadXX);
		m->setFitness(_distanceMatrix, _flowMatrix);
		_members.push_back(m);
	}
}

Population::Population(std::vector<Member*> members, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	_amount = members.size();
	_members = members;
	_hadXX = hadXX;
	_distanceMatrix = distanceMatrix;
	_flowMatrix = flowMatrix;
	for (int i = 0; i < _amount; i++) {
		_members[i]->setFitness(_distanceMatrix, _flowMatrix);
	}
}

Population::~Population()
{
	for (int i = 0; i < _amount; i++)
	{
		delete _members[i];
		delete _nextGen[i];
		delete _matingPool[i];
	}
	
	_members.clear();
	_nextGen.clear();
	_matingPool.clear();
	cout << "we died" << endl;
}

void Population::select(int x)
{
	vector<Member*> competitors;
	vector<int> fitnesses;

	for (int i = 0; i < x; i++) {
		int r = (rand() % _amount);
		competitors.push_back(_members.at(r));
		fitnesses.push_back(_members.at(r)->getFitness());
	}
	
	for (int i = 0; i < x; i++)
	{
		for (int j = i; j < x; j++)
		{
			if (fitnesses[i] > fitnesses[j])
			{
				swap(fitnesses.at(i), fitnesses.at(j));
				swap(competitors.at(i), competitors.at(j));
			}
		}
	}
	_matingPool.push_back(competitors[0]);
	competitors.clear();
}

void Population::crossover(int index)
{
	vector<int> parent_1 = _matingPool[index * 2]->getGenes();
	vector<int> parent_2 = _matingPool[index * 2 + 1]->getGenes();

	float px =  (float)rand() / RAND_MAX;
	if (px < _px) {
		vector<int> offspring_1;
		vector<int> offspring_2;

		int sub = _hadXX / 2;

		int r = (rand() % sub);
		map<int, int> m_1;
		map<int, int> m_2;

		for (int i = r; i < r + sub; i++)
		{
			int p_1 = parent_1[i];
			int p_2 = parent_2[i];
			m_1[p_2] = p_1;
			m_2[p_1] = p_2;
		}

		for (int i = 0; i < _hadXX; i++)
		{
			if (i < r || i >= r + sub)
			{
				offspring_1.push_back(parent_1[i]);
				offspring_2.push_back(parent_2[i]);
			}
			else
			{
				offspring_1.push_back(parent_2[i]);
				offspring_2.push_back(parent_1[i]);
			}
		}

		map<int, int>::iterator it;

		int changes = 0;
		while (changes != sub)
		{
			changes = 0;
			for (int i = 0; i < _hadXX; i++)
			{
				if (i < r || i >= r + sub)
				{
					it = m_1.find(offspring_1[i]);
					if (it != m_1.end())
					{
						offspring_1[i] = it->second;
					}
					else
					{
						changes++;
					}
				}
			}
		}

		changes = 0;
		while (changes != sub)
		{
			changes = 0;
			for (int i = 0; i < _hadXX; i++)
			{
				if (i < r || i >= r + sub)
				{
					it = m_2.find(offspring_2[i]);
					if (it != m_2.end())
					{
						offspring_2[i] = it->second;
					}
					else
					{
						changes++;
					}
				}
			}
		}
		_nextGen.push_back(new Member(offspring_1));
		_nextGen.push_back(new Member(offspring_2));
	}
	else
	{
		_nextGen.push_back(new Member(parent_1));
		_nextGen.push_back(new Member(parent_2));
	}
}

void Population::mutate(int index)
{
	vector<int> member = _nextGen[index]->getGenes();
	float pm;
	int r;
	for (int i = 0; i < _hadXX; i++)
	{
		//std::mt19937 engine(static_cast<int>(time(NULL)));
		//std::uniform_real_distribution<float> distribution(0.0, 1.0);
		//auto random = std::bind(distribution, engine);
		pm = (float)rand() / RAND_MAX;
		if (pm < _pm)
		{
			r = (rand() % _hadXX);
			swap(member[i], member[r]);
		}
	}
	_nextGen[index]->setGenes(member);
}

int Population::getBest()
{
	vector<int> fitnesses;

	for (int i = 0; i < _amount; i++) {
		fitnesses.push_back(_members.at(i)->getFitness());
	}

	for (int i = 0; i < _amount; i++)
	{
		for (int j = i; j < _amount; j++)
		{
			if (fitnesses[i] > fitnesses[j])
			{
				swap(fitnesses.at(i), fitnesses.at(j));
			}
		}
	}

	return fitnesses[0];
}

int Population::getWorst()
{
	vector<int> fitnesses;

	for (int i = 0; i < _amount; i++) {
		fitnesses.push_back(_members.at(i)->getFitness());
	}

	for (int i = 0; i < _amount; i++)
	{
		for (int j = i; j < _amount; j++)
		{
			if (fitnesses[i] < fitnesses[j])
			{
				swap(fitnesses.at(i), fitnesses.at(j));
			}
		}
	}

	return fitnesses[0];
}

int Population::getAvg()
{
	int fitness = 0;

	for (int i = 0; i < _amount; i++) {
		fitness += _members.at(i)->getFitness();
	}
	fitness /= _amount;
	return fitness;
}



void Population::setDistanceAndFlow(vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix)
{
	_distanceMatrix = distanceMatrix;
	_flowMatrix = flowMatrix;
}
