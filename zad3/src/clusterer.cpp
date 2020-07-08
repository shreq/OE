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

void Clusterer::updateFitness()
{
    for (auto creature : creatures)
    {
        creature->updateFitness();
    }

    sort(creatures.begin(), creatures.end(), [](Creature *a, Creature *b) {
        return a->getFitness() < b->getFitness();
    });
}

Creature *Clusterer::selection()
{
    double fitnessSum = 0;
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
    auto creaturesNew = vector<Creature *>();

    if (elitism)
    {
        creaturesNew.emplace_back(creatures[0]);
    }

    for (unsigned int i = (elitism ? 1 : 0); i < creatures.size(); i++)
    {
        Creature *a = selection();
        Creature *b = selection();
        while (a == b)
        {
            b = selection();
        }

        creaturesNew.emplace_back(crossover(a, b));
    }

    creatures = creaturesNew;
    mutate();
    generation++;
}
