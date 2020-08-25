#include "../../include/fitness/weightedFitness.hpp"
#include "../../include/fitness/fitness.hpp"
#include <vector>

using namespace std;

WeightedFitness::WeightedFitness(Fitness *fitness, double weight) : fitness(fitness), weight(weight) {}

WeightedFitness::~WeightedFitness() {}

WeightedFitness * WeightedFitness::clone() const
{
    return new WeightedFitness(*this);
}

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

double WeightedFitness::getWeight()
{
    return weight;
}
