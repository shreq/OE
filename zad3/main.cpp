#include "include/point.hpp"
#include "include/creature.hpp"
#include "include/clusterer.hpp"
#include "include/utils.hpp"
#include <iostream>

using namespace std;

int main()
{
	auto clusterer = Clusterer(readCsv("resources/credit_card_pca.csv"), 10);

	return 0;
}
