#include "../../include/fitness/dunnIndex.hpp"
#include "../../include/fitness/fitness.hpp"
#include "../../include/cluster.hpp"
#include "../../include/point.hpp"
#include "../../include/utils.hpp"
#include <vector>

using namespace std;

DunnIndex::~DunnIndex() {}

void DunnIndex::updateValue(vector<Cluster *> clusters)
{
    double minCenterDistance = minimalCenterDistance(clusters);
    double maxClusterDistance = maximalClusterDistance(clusters);

    value = minCenterDistance / maxClusterDistance;
}

DunnIndex * DunnIndex::clone() const
{
    return new DunnIndex(*this);
}

bool DunnIndex::operator>(const Fitness &other)
{
    return value > other.getValue();
}

double DunnIndex::minimalCenterDistance(std::vector<Cluster *> clusters)
{
    double minValue = LONG_MAX;
    for (auto i : clusters)
    {
        for (auto j : clusters)
        {
            if (i != j && !j->isEmpty())
            {
                double dist = distanceOfCenters(i, j);
                if (dist < minValue)
                {
                    minValue = dist;
                }
            }
        }
    }
    return minValue;
}

double DunnIndex::maximalClusterDistance(std::vector<Cluster *> clusters)
{
    double maxValue = LONG_MIN;
    for (auto i : clusters)
    {
        if (!i->isEmpty())
        {
            double avgDist = averageDistance(i);
            if (avgDist > maxValue)
            {
                maxValue = avgDist;
            }
        }
    }
    return maxValue;
}
