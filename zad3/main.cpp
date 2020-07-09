#include "include/point.hpp"
#include "include/creature.hpp"
#include "include/clusterer.hpp"
#include "include/utils.hpp"
#include <iostream>

using namespace std;

int main()
{
	auto clusterer = Clusterer(10);

	clusterer.evolve(10);

	return 0;
}
