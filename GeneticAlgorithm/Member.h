#pragma once
#include <vector>
#include <algorithm>  
using namespace std;

class Member
{
private:
	int _length;
	std::vector<int> _genes;
	int _fitness;
	
public:
	Member(int length);
	Member(std::vector<int> genes);
	~Member();
	void print();
	std::vector<int> getGenes() { return _genes; };
	void setGenes(std::vector<int> genes) { _genes = genes; }
	void setFitness(vector<vector<int>> distanceMatrix, vector<vector<int>> flowMatrix);
	int getFitness() { return _fitness; };
};

