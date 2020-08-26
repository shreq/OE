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

int main()
{
	auto daves = new DavesBouldin();
	auto dunn = new DunnIndex();
	auto sil = new Silhouette();
	auto comp = new ComplexFitness();
	comp->add(daves, 4);
	comp->add(dunn, 1);
	comp->add(sil, 3);
	auto clusterer = Clusterer(readCsv("resources/credit_card_pca.csv"), 10, comp);
	clusterer.evolve(2);

	cout << "~~~~Best creature:" << "\n";
	int i = 0;
	for (auto center: clusterer.getCreatures()[0]->getCenters())
	{
		cout << "Center " << ++i << "\n";
		cout << "X = " << center->getX() << "\n";
		cout << "Y = " << center->getY() << "\n";
	}
	cout << "\nBest creature fitness value: " << clusterer.getCreatures()[0]->getFitnessValue();
	return 0;
}
