#include "../include/utils.hpp"
#include "../include/point.hpp"
#include "../include/cluster.hpp"
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

/* #region settings */
bool elitism = true;

int centerRangeMin = -50;
int centerRangeMax = 50;

unsigned int centersCountMin = 2;
unsigned int centersCountMax = 10;

double centerMoveMutationRate = 0.25;
double centerRemoveMutationRate = 0.25;
double centerAddMutationRate = 0.25;
/* #endregion settings */

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_real_distribution<double> uniform_distribution(0.0, 1.0);
std::normal_distribution<double> normal_distribution(0, 5);

int getRandomInt()
{
    return generator();
}

double getRandomDouble()
{
    return uniform_distribution(generator);
}

double getRandomGaussian()
{
    return normal_distribution(generator);
}

bool willMutate(double mutationRate)
{
    return (getRandomDouble() < mutationRate);
}

std::vector<Point *> readCsv(std::string filepath)
{
    auto result = std::vector<Point *>();
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    else if (!file.good())
    {
        throw std::runtime_error("Error reading file");
    }

    std::string row, cell;
    while (std::getline(file, row))
    {
        std::stringstream ss(row);
        auto values = std::vector<double>();

        while (std::getline(ss, cell, ','))
        {
            values.emplace_back(std::stod(cell));
        }

        result.emplace_back(new Point(values.at(0), values.at(1)));
    }

    return result;
}

double averageDistance(Point *point, std::vector<Point *> otherPoints)
{
    double distSum = 0.0;
    if (otherPoints.size() == 0)
    {
        return 0;
    }
    for (auto i : otherPoints)
    {
        if (point != i)
        {
            double dist = point->euclideanDistance(i);
            distSum += dist;
        }
    }
    return distSum / (double)otherPoints.size();
}

double averageDistance(Cluster *cluster)
{
    return averageDistance(cluster->getCenter(), cluster->getPoints());
}

double distanceOfCenters(Cluster *first, Cluster *second)
{
    return first->getCenter()->euclideanDistance(second->getCenter());
}
