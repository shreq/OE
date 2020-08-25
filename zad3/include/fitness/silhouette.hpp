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
    long minimalAverageDistanceToOtherClusters(Point *point, Cluster *pointCluster, std::vector<Cluster *> clusters);

public:
    bool operator>(const Fitness &other);
    void updateValue(std::vector<Cluster *> clusters);
};
