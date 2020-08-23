#include "../../include/fitness/davesBouldin.hpp"
#include "../../include/fitness/fitness.hpp"
#include "../../include/cluster.hpp"
#include "../../include/point.hpp"
#include "../../include/utils.hpp"
#include <vector>

using namespace std;

void DavesBouldin::updateValue(vector<Cluster *> clusters)
{
    long sum = 0;

    for (auto i : clusters) 
    {
        sum += maxDistance(i, clusters);
    }

    value =  1 / clusters.size() * sum;
}

bool DavesBouldin::operator>(const Fitness &other)
{
    return value < other.getValue();
}

long DavesBouldin::maxDistance(Cluster * i, vector<Cluster *> clusters)
{
    long maxValue = LONG_MIN;
    for (auto j : clusters)
    {
        if (i != j)
        {
            long dist = distance(i, j);
            if (dist > maxValue)
                maxValue = dist;
        }
    }
    return maxValue;
}

long DavesBouldin::distance(Cluster * i, Cluster * j)
{
    long sumOfAvgDistances = averageDistance(i) + averageDistance(j);
    long centerDistance = distanceOfCenters(i, j);

    return sumOfAvgDistances / centerDistance;
}