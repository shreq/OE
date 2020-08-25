#include "../../include/fitness/complexFitness.hpp"
#include "../../include/fitness/weightedFitness.hpp"
#include "../../include/fitness/fitness.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

ComplexFitness::ComplexFitness() : fitnessList(vector<WeightedFitness *>()) {}

ComplexFitness::~ComplexFitness() {}

void ComplexFitness::add(Fitness *fitness, long weight)
{
    fitnessList.emplace_back(new WeightedFitness(fitness, weight));
}

void ComplexFitness::updateValue(std::vector<Cluster *> clusters)
{
    for (auto fitness : fitnessList)
    {
        fitness->updateValue(clusters);
    }
}

bool ComplexFitness::operator>(const ComplexFitness &other)
{
    if (fitnessList.size() != other.fitnessList.size())
    {
        throw runtime_error("Unable to compare complex fitness with different components");
    }

    long sum = 0;

    for (unsigned int i = 0; i < fitnessList.size(); i++)
    {
        bool isFitnessBetter = fitnessList[0]->operator>(other.fitnessList[0]);
        long w = fitnessList[0]->getWeight();
        isFitnessBetter ? sum += w : sum -= w;
    }

    return sum > 0;
}
