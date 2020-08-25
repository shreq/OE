#include "include/point.hpp"
#include "include/creature.hpp"
#include "include/clusterer.hpp"
#include "include/utils.hpp"
#include "include/fitness/davesBouldin.hpp"
#include "include/fitness/dunnIndex.hpp"
#include "include/fitness/silhouette.hpp"
#include <iostream>

using namespace std;

int main()
{
	auto clusterer = Clusterer(readCsv("resources/credit_card_pca.csv"), 10, new Silhouette());
	clusterer.evolve(1);

	return 0;
}
