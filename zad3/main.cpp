#include "include/point.hpp"
#include "include/creature.hpp"
#include "include/clusterer.hpp"
#include "include/utils.hpp"
#include "include/fitness/davesBouldin.hpp"
#include "include/fitness/dunnIndex.hpp"
#include "include/fitness/silhouette.hpp"
#include "include/fitness/complexFitness.hpp"
#include <iostream>

using namespace std;

Fitness *inputFitness();
void printResult(Creature *creature);
void lameClrScr();

int main()
{
	unsigned int populationSize, numberOfGenerations, elitism_;
	double mutationRate, addMutationRate, removeMutationRate;
	lameClrScr();

	auto fitness = inputFitness();
	cout << "Enter population size:        ";
	cin >> populationSize;
	cout << "Enter number of generations:  ";
	cin >> numberOfGenerations;
	cout << "Enable elitism? [1 / 0]       ";
	cin >> elitism_;
	elitism = elitism_ == 0 ? false : true;
	cout << "Enter 'modify gene' mutation rate [0, 1]:   ";
	cin >> mutationRate;
	cout << "Enter 'add new gene' mutation rate [0, 1]:   ";
	cin >> addMutationRate;
	cout << "Enter 'remove gene' mutation rate [0, 1]:   ";
	cin >> removeMutationRate;
	centerMoveMutationRate = mutationRate;
	centerAddMutationRate = addMutationRate;
	centerRemoveMutationRate = removeMutationRate;

	auto clusterer = Clusterer(readCsv("resources/cats-data-pca.csv"), populationSize, fitness);
	clusterer.evolve(numberOfGenerations);

	printResult(clusterer.getCreatures()[0]);
	return 0;
}

Fitness *inputFitness()
{
	short method;
	do
	{
		cout << "Choose fitness method:\n"
			 << "[1] Davies-Bouldin\n"
			 << "[2] Dunn\n"
			 << "[3] Silhouette\n"
			 << "[4] Complex           ";
		cin >> method;
	} while (method < 1 || 4 < method);

	switch (method)
	{
	case 1:
		return new DavesBouldin();
	case 2:
		return new DunnIndex();
	case 3:
		return new Silhouette();
	default:
		lameClrScr();
		double weights[3];
		cout << "Enter Davies-Bouldin weight:  ";
		cin >> weights[0];
		cout << "Enter Dunn weight             ";
		cin >> weights[1];
		cout << "Enter Silhouette weight:      ";
		cin >> weights[2];

		auto complex = new ComplexFitness();
		complex->add(new DavesBouldin(), weights[0]);
		complex->add(new DunnIndex(), weights[1]);
		complex->add(new Silhouette(), weights[2]);
		return complex;
	}
}

void printResult(Creature *creature)
{
	cout << "\nBest creature achieved fitness = " << creature->getFitnessValue() << '\n';

	int i = 1;
	for (auto center : creature->getCenters())
	{
		cout << "Center #" << i++ << '\n'
			 << " x = " << center->getX() << '\n'
			 << " y = " << center->getY() << '\n';
	}
}

void lameClrScr()
{
	cout << string(100, '\n');
}
