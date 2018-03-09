#pragma once
#include <vector>
#include "Member.h"

class Population
{
private:
	int _hadXX;
	int _amount;
	float _px = 0.2;// 0.50;
	float _pm = 0.05;// 0.05;
	
	std::vector<Member*> _members;
	std::vector<Member*> _matingPool;
	std::vector<Member*> _nextGen;

	vector<vector<int>> _distanceMatrix;
	vector<vector<int>> _flowMatrix;

public:
	
	Population(int amount, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix);
	Population(std::vector<Member*> members, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix);
	~Population();

	vector<Member*> getNextGen() { return _nextGen; }

	void select(int x);
	void crossover(int index);
	void mutate(int index);
	
	int getBest();
	int getWorst();
	int getAvg();

	float getPx() { return _px; }

	void setDistanceAndFlow(vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix);
};

