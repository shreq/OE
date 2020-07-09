#include "../include/creature.hpp"
#include "../include/point.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Creature::Creature()
{
    centers = vector<Point *>();
    for (unsigned int i = 0; i < max(centersCountMin, getRandomInt() % (centersCountMax + 1)); i++)
    {
        centers.emplace_back(new Point());
    }
    updateFitness();
}

Creature::Creature(vector<Point *> centers) : centers(centers)
{
    updateFitness();
}

Creature::~Creature() {}

vector<Point *> Creature::getCenters()
{
    return centers;
}

double Creature::getFitness()
{
    return fitness;
}

bool Creature::operator==(const Creature &creature)
{
    return (this == &creature);
}

void Creature::removeCenter()
{
    if (centers.size() > centersCountMin && willMutate(centerRemoveMutationRate))
    {
        centers.erase(centers.begin() + getRandomInt() % centers.size());
    }
}

void Creature::addCenter()
{
    if (centers.size() < centersCountMax && willMutate(centerAddMutationRate))
    {
        centers.insert(centers.begin() + getRandomInt() % centers.size(), new Point());
    }
}

void Creature::updateFitness()
{
    /// TODO: implement
}

void Creature::mutate()
{
    removeCenter();
    addCenter();

    for (auto center : centers)
    {
        center->mutate();
    }

    updateFitness();
}
