#include "../include/creature.hpp"
#include "../include/point.hpp"
#include "../include/utils.hpp"
#include "../include/cluster.hpp"
#include "../include/fitness/fitness.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

Creature::Creature(vector<Point *> data, Fitness * fitness) : centers(vector<Point *>()), data(data), fitness(fitness)
{
    for (unsigned int i = 0; i < max(centersCountMin, getRandomInt() % (centersCountMax + 1)); i++)
    {
        centers.emplace_back(new Point());
    }
    updateFitness();
}

Creature::Creature(vector<Point *> centers, vector<Point *> data, Fitness * fitness) : centers(centers), data(data), fitness(fitness)
{
    updateFitness();
}

Creature::~Creature() {}

vector<Point *> Creature::getCenters()
{
    return centers;
}

double Creature::getFitnessValue()
{
    return fitness->getValue();
}

Fitness * Creature::getFitness()
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
    auto clusters = calculateClusters();
    fitness->updateValue(clusters);
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

vector<Cluster *> Creature::calculateClusters()
{
    auto clusters = map<Point *, vector<Point *>>();
    for (auto center : centers)
    {
        clusters[center] = vector<Point *>();
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

        clusters[closestCenter].emplace_back(point);
    }

    auto result = vector<Cluster *>();
    for (auto &cluster : clusters) 
    {
        auto center = cluster.first;
        auto points = cluster.second;
        result.emplace_back(new Cluster(center, points));
    }
    return result;
}
