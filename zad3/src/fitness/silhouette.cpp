#include "../../include/fitness/silhouette.hpp"
#include "../../include/fitness/fitness.hpp"
#include "../../include/cluster.hpp"
#include "../../include/point.hpp"
#include "../../include/utils.hpp"
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

void Silhouette::updateValue(vector<Cluster *> clusters)
{
    long pointValueSum = 0.0;
    long nOfPoints = 0.0;
    for (auto cluster : clusters)
    {
        for(auto i : cluster->getPoints())
        {
            long avgDistInCluster = averageDistance(i, cluster->getPoints());
            long minAvgDistToOtherClusters = minimalAverageDistanceToOtherClusters(i, cluster, clusters);

            long pointValue = (minAvgDistToOtherClusters - avgDistInCluster) / max(minAvgDistToOtherClusters, avgDistInCluster);
            
            pointValueSum += pointValue;
            nOfPoints++;
        }
    }
    value = pointValueSum / nOfPoints;
}

bool Silhouette::operator>(const Fitness &other)
{
    return value > other.getValue();
}

long Silhouette::minimalAverageDistanceToOtherClusters(Point * point, Cluster * pointCluster, std::vector<Cluster *> clusters)
{
    long minValue = LONG_MAX;
    for (auto i : clusters)
    {
        if (i != pointCluster)
        {
            long dist = averageDistance(point, i->getPoints());
            if (dist < minValue)
            {
                minValue = dist;
            }
        }
    }
    return minValue;
}