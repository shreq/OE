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
    long minCenterDistance = minimalCenterDistance(clusters);
    long maxClusterDistance = maximalClusterDistance(clusters);

    value = minCenterDistance / maxClusterDistance;
}

bool DunnIndex::operator>(const Fitness &other)
{
    return value > other.getValue();
}

long DunnIndex::minimalCenterDistance(std::vector<Cluster *> clusters)
{
    long minValue = LONG_MAX;
    for (auto i : clusters)
    {
        for (auto j : clusters)
        {
            if (i != j)
            {
                long dist = distanceOfCenters(i, j);
                if (dist < minValue)
                {
                    minValue = dist;
                }
            }
        }
    }
}

long DunnIndex::maximalClusterDistance(std::vector<Cluster *> clusters)
{
    long maxValue = LONG_MIN;
    for (auto i : clusters)
    {
        long avgDist = averageDistance(i);
        if (avgDist > maxValue)
        {
            maxValue = avgDist;
        }
    }
}
