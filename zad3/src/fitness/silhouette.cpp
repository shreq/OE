#include "../../include/fitness/silhouette.hpp"
#include "../../include/fitness/fitness.hpp"
#include "../../include/cluster.hpp"
#include "../../include/point.hpp"
#include "../../include/utils.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

Silhouette::~Silhouette() {}

void Silhouette::updateValue(vector<Cluster *> clusters)
{
    double pointValueSum = 0.0;
    double nOfPoints = 0.0;
    for (auto cluster : clusters)
    {
        for (auto i : cluster->getPoints())
        {
            double avgDistInCluster = averageDistance(i, cluster->getPoints());
            double minAvgDistToOtherClusters = minimalAverageDistanceToOtherClusters(i, cluster, clusters);

            double pointValue = (minAvgDistToOtherClusters - avgDistInCluster) / max(minAvgDistToOtherClusters, avgDistInCluster);
            
            pointValueSum += pointValue;
            nOfPoints++;
        }
    }
    value = pointValueSum / (double) nOfPoints;
}

Silhouette * Silhouette::clone() const
{
    return new Silhouette(*this);
}

bool Silhouette::operator>(const Fitness &other)
{
    return value > other.getValue();
}

double Silhouette::minimalAverageDistanceToOtherClusters(Point *point, Cluster *pointCluster, std::vector<Cluster *> clusters)
{
    double minValue = LONG_MAX;
    for (auto i : clusters)
    {
        if (i != pointCluster)
        {
            double dist = averageDistance(point, i->getPoints());
            if (dist < minValue)
            {
                minValue = dist;
            }
        }
    }
    return minValue;
}
