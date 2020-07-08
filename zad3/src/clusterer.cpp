#include "../include/clusterer.hpp"
#include "../include/creature.hpp"
#include "utils.cpp"
#include <cmath>

using namespace std;

Clusterer::Clusterer(unsigned int populationSize)
{
    creatures = vector<Creature *>();
    for (unsigned int i = 0; i < populationSize; i++)
    {
        creatures.emplace_back(new Creature());
    }
}

Clusterer::~Clusterer() {}

vector<Creature *> Clusterer::getCreatures()
{
    return creatures;
}

void Clusterer::updateFitness()
{
    for (auto creature : creatures)
    {
        creature->updateFitness();
    }
}

Creature *Clusterer::selection()
{
    /// TODO: implement
}

Creature *Clusterer::crossover(Creature *creatureA, Creature *creatureB)
{
    unsigned int length = min(creatureA->getCenters().size(), creatureB->getCenters().size());
    auto centers = vector<Point *>(length);

    for (unsigned int i = 0; i < length; i++)
    {
        if (getRandomDouble() < 0.5)
        {
            centers[i] = creatureA->getCenters()[i];
        }
        else
        {
            centers[i] = creatureB->getCenters()[i];
        }
    }

    return new Creature(centers);
}

void Clusterer::mutate()
{
    for (auto creature : creatures)
    {
        creature->mutate();
    }
}

void Clusterer::evolve()
{
    /// TODO: implement
}
