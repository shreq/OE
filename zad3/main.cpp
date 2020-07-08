#include "include/point.hpp"
#include "include/creature.hpp"
#include "include/clusterer.hpp"
#include "include/utils.hpp"
#include <iostream>

using namespace std;

int main()
{
	auto clusterer = Clusterer(50);

	clusterer.evolve(1000);

	return 0;
}
