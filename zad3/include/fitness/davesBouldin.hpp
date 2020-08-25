#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class DavesBouldin : public Fitness
{
public:
    virtual ~DavesBouldin();

private:
    long maxDistance(Cluster *i, std::vector<Cluster *> clusters);
    long distance(Cluster *i, Cluster *j);

public:
    bool operator>(const Fitness &other);
    void updateValue(std::vector<Cluster *> clusters);
};
