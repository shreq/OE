#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;
class Point;

class Silhouette : public Fitness
{
public:
    virtual ~Silhouette();

private:
    double minimalAverageDistanceToOtherClusters(Point *point, Cluster *pointCluster, std::vector<Cluster *> clusters);

public:
    virtual Silhouette *clone() const;
    virtual bool operator>(const Fitness &other);
    virtual void updateValue(std::vector<Cluster *> clusters);
};
