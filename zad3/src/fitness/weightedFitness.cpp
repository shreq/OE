#include "../../include/fitness/weightedFitness.hpp"
#include "../../include/fitness/fitness.hpp"
#include <vector>

using namespace std;

WeightedFitness::WeightedFitness(Fitness *fitness, long weight) : fitness(fitness), weight(weight) {}

WeightedFitness::~WeightedFitness() {}

bool WeightedFitness::operator>(const Fitness &other)
{
    return fitness->operator>(other);
}

bool WeightedFitness::operator>(WeightedFitness *other)
{
    return fitness->operator>(*other);
}

void WeightedFitness::updateValue(std::vector<Cluster *> clusters)
{
    fitness->updateValue(clusters);
    value = weight * fitness->getValue();
}

long WeightedFitness::getWeight()
{
    return weight;
}
