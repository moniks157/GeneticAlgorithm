#pragma once
#include <vector>

using namespace std;
class Algorithm
{
private:
	int _hadXX;
	int _amount;
	float _px = 0.2f;// 0.50;
	float _pm = 0.05f;// 0.05;

	vector<vector<int>> _distanceMatrix;
	vector<vector<int>> _flowMatrix;

	vector<vector<int>> _members;
	vector<vector<int>> _nextGen;
	vector<vector<int>> _matingPool;

	vector<int> _fitness;

public:
	Algorithm(int amount, int hadXX, vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix);
	~Algorithm();

	void select(int x);
	void crossover(int index);
	void mutate(int index);

	void setFitness(int index);

	int getBest();
	int getWorst();
	int getAvg();
};

