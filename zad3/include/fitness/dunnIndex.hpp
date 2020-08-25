#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class DunnIndex : public Fitness
{
public:
    virtual ~DunnIndex();

private:
    double minimalCenterDistance(std::vector<Cluster *> clusters);
    double maximalClusterDistance(std::vector<Cluster *> clusters);

public:
    virtual DunnIndex *clone() const;
    virtual bool operator>(const Fitness &other);
    virtual void updateValue(std::vector<Cluster *> clusters);
};
