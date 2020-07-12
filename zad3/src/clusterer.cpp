#include "../include/clusterer.hpp"
#include "../include/point.hpp"
#include "../include/creature.hpp"
#include "../include/utils.hpp"
#include <cmath>
#include <algorithm>
#include <exception>

using namespace std;

Clusterer::Clusterer(vector<Point *> data, unsigned int populationSize) : data(data), creatures(vector<Creature *>()), generation(0)
{
    for (unsigned int i = 0; i < populationSize; i++)
    {
        creatures.emplace_back(new Creature());
    }
    creatures = sortByFitness(creatures);
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

vector<Creature *> Clusterer::sortByFitness(vector<Creature *> creatures)
{
    sort(creatures.begin(), creatures.end(), [](Creature *a, Creature *b) {
        return a->getFitness() > b->getFitness();
    });
    return creatures;
}

vector<Creature *> Clusterer::selection(unsigned int numberOfSelected)
{
    if (numberOfSelected > creatures.size())
    {
        throw runtime_error("Number of creatures to select bigger than population");
    }

    auto selected = vector<Creature *>();
    for (unsigned int i = 0; i < numberOfSelected;)
    {
        Creature *creature = rouletteSelection();
        if (find(selected.begin(), selected.end(), creature) == selected.end())
        {
            selected.emplace_back(creature);
            i++;
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
        auto *child = randomCrossover(selection(2));
        child->mutate();
        creaturesNew.emplace_back(child);
    }

    return sortByFitness(creaturesNew);
}

void Clusterer::evolve(unsigned int generations)
{
    for (; generation < generations; generation++)
    {
        creatures = generateOffspring();
    }
}

map<Point *, vector<Point *>> Clusterer::cluster()
{
    auto centers = creatures.at(0)->getCenters();

    auto result = map<Point *, vector<Point *>>();
    for (auto center : centers)
    {
        result[center] = vector<Point *>();
    }

    for (auto point : data)
    {
        Point *closestCenter = centers.at(0);
        double lowestDistance = point->euclideanDistance(centers.at(0));

        for (unsigned int i = 1; i < centers.size(); i++)
        {
            double distance = point->euclideanDistance(centers[i]);
            if (distance < lowestDistance)
            {
                lowestDistance = distance;
                closestCenter = centers[i];
            }
        }

        result[closestCenter].emplace_back(point);
    }

    return result;
}
