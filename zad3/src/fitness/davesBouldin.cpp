#include "../../include/fitness/davesBouldin.hpp"
#include "../../include/fitness/fitness.hpp"
#include "../../include/cluster.hpp"
#include "../../include/point.hpp"
#include "../../include/utils.hpp"
#include <vector>

using namespace std;

DavesBouldin::~DavesBouldin() {}

void DavesBouldin::updateValue(vector<Cluster *> clusters)
{
    double sum = 0;

    for (auto i : clusters)
    {
        sum += maxDistance(i, clusters);
    }

    value = 1.0 / clusters.size() * sum;
}

DavesBouldin * DavesBouldin::clone() const
{
    return new DavesBouldin(*this);
}

bool DavesBouldin::operator>(const Fitness &other)
{
    return value < other.getValue();
}

double DavesBouldin::maxDistance(Cluster *i, vector<Cluster *> clusters)
{
    double maxValue = LONG_MIN;
    for (auto j : clusters)
    {
        if (i != j && !j->isEmpty())
        {
            double dist = distance(i, j);
            if (dist > maxValue)
                maxValue = dist;
        }
    }
    return maxValue;
}

double DavesBouldin::distance(Cluster *i, Cluster *j)
{
    double sumOfAvgDistances = averageDistance(i) + averageDistance(j);
    double centerDistance = distanceOfCenters(i, j);

    return sumOfAvgDistances / centerDistance;
}
