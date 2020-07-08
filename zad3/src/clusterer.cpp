#include "../include/clusterer.hpp"
#include "../include/creature.hpp"
#include "../include/utils.hpp"
#include <cmath>
#include <algorithm>

using namespace std;

Clusterer::Clusterer(unsigned int populationSize)
{
    creatures = vector<Creature *>();
    for (unsigned int i = 0; i < populationSize; i++)
    {
        creatures.emplace_back(new Creature());
    }
    sortByFitness();
    generation = 0;
}

Clusterer::~Clusterer() {}

vector<Creature *> Clusterer::getCreatures()
{
    return creatures;
}

unsigned int Clusterer::getGeneration()
{
    return generation;
}

Creature *Clusterer::rouletteSelection()
{
    double fitnessSum = 0.0;
    for (auto creature : creatures)
    {
        fitnessSum += creature->getFitness();
    }

    double random = getRandomDouble() * fitnessSum;

    for (auto creature : creatures)
    {
        random -= creature->getFitness();
        if (random < 0)
        {
            return creature;
        }
    }

    return creatures.back();
}

Creature *Clusterer::randomCrossover(vector<Creature *> parents)
{
    unsigned int length = parents[0]->getCenters().size();
    for (unsigned int i = 1; i < parents.size(); i++)
    {
        if (parents[i]->getCenters().size() < length)
        {
            length = parents[i]->getCenters().size();
        }
    }

    auto centers = vector<Point *>(length);
    for (unsigned int i = 0; i < length; i++)
    {
        centers[i] = parents[getRandomInt() % parents.size()]->getCenters()[i];
    }

    return new Creature(centers);
}

inline void Clusterer::sortByFitness()
{
    sort(creatures.begin(), creatures.end(), [](Creature *a, Creature *b) {
        return a->getFitness() < b->getFitness();
    });
}

vector<Creature *> Clusterer::selection(unsigned int numberOfSelected)
{
    if (numberOfSelected > creatures.size())
    {
        throw; // FIXME: throw some proper exception
    }

    auto selected = vector<Creature *>();
    for (unsigned int i = 0; i < numberOfSelected; i++)
    {
        Creature *creature = rouletteSelection();
        if (find(selected.begin(), selected.end(), creature) != selected.end())
        {
            selected.emplace_back(creature);
        }
    }

    return selected;
}

vector<Creature *> Clusterer::generateOffspring()
{
    auto creaturesNew = vector<Creature *>();

    if (elitism)
    {
        creaturesNew.emplace_back(creatures[0]);
    }

    for (unsigned int i = (elitism ? 1 : 0); i < creatures.size(); i++)
    {
        Creature *child = randomCrossover(selection(2));
        child->mutate();
        child->updateFitness();
        creaturesNew.emplace_back(child);
    }

    return creaturesNew;
}

void Clusterer::evolve(unsigned int generations)
{
    for (; generation < generations; generation++)
    {
        creatures = generateOffspring();
        sortByFitness();
    }
}