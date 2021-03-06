// GeneticAlgorithm.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <fstream> 
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Population.h"

using namespace std;

int main()
{
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		int gen = 10;
		srand((int)time(0));

		fstream fs;
		string file;
		cout << "Podaj nazwe pliku: ";
		cin >> file;

		fs.open(file, std::fstream::in);

		int hadXX;
		vector<vector<int>>distanceMatrix;
		vector<vector<int>>flowMatrix;

		fs >> hadXX;

		int elem;

		for (int i = 0; i < hadXX; i++) {
			vector<int> row;
			for (int j = 0; j < hadXX; j++) {
				fs >> elem;
				row.push_back(elem);
			}
			distanceMatrix.push_back(row);
		}

		for (int i = 0; i < hadXX; i++) {
			vector<int> row;
			for (int j = 0; j < hadXX; j++) {
				fs >> elem;
				row.push_back(elem);
			}
			flowMatrix.push_back(row);
		}

		fs.close();
		file = "wynik" + to_string(hadXX) + ".csv";
		fs.open(file, std::fstream::out);
		Population* p = new Population(gen, hadXX, distanceMatrix, flowMatrix);
		fs << p->getBest() << ";" << p->getWorst() << ";" << p->getAvg() << ";\n";
		for (int j = 0; j < gen - 1; j++) {
			for (int i = 0; i < gen; i++)
			{
				p->select(2);
			}

			for (int i = 0; i < gen / 2; i++)
			{
				p->crossover(i);
			}

			for (int i = 0; i < gen; i++)
			{
				p->mutate(i);
			}
			fs << p->getBest() << ";" << p->getWorst() << ";" << p->getAvg() << ";\n";

			p->setMembers(p->getNextGen());
			cout << "gen " << j << endl;
		}
		delete p;

		Member* m = new Member(vector<int>{2});
		m->greedy(distanceMatrix,flowMatrix);
		m->print();
		cout << " " << m->getFitness();
		delete m;
		distanceMatrix.clear();
		flowMatrix.clear();
		
		fs.close();
		file.clear();

		system("PAUSE");
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

