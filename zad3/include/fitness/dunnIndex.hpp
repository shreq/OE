#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class DunnIndex : public Fitness
{
public:
    virtual ~DunnIndex();

private:
    long minimalCenterDistance(std::vector<Cluster *> clusters);
    long maximalClusterDistance(std::vector<Cluster *> clusters);

public:
    bool operator>(const Fitness &other);
    void updateValue(std::vector<Cluster *> clusters);
};
