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
    for (auto cluster : clusters)
    {
        double avgDistInCluster = averageDistance(cluster);
        double minAvgDistToOtherClusters = minimalAverageDistanceToOtherClusters(cluster, clusters);

        double max_ = max(minAvgDistToOtherClusters, avgDistInCluster);
        if (max_ != 0)
        {
            double pointValue = (minAvgDistToOtherClusters - avgDistInCluster) / max(minAvgDistToOtherClusters, avgDistInCluster);
            pointValueSum += pointValue;
        }

    }
    value = pointValueSum / (double) clusters.size() + 1.0;
}

Silhouette * Silhouette::clone() const
{
    return new Silhouette(*this);
}

bool Silhouette::operator>(const Fitness &other)
{
    return value > other.getValue();
}

double Silhouette::minimalAverageDistanceToOtherClusters(Cluster *cluster, std::vector<Cluster *> clusters)
{
    double minValue = LONG_MAX;
    for (auto i : clusters)
    {
        if (i != cluster)
        {
            double dist = averageDistance(cluster->getCenter(), i->getPoints());
            if (dist < minValue)
            {
                minValue = dist;
            }
        }
    }
    return minValue;
}
