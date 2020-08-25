#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class DavesBouldin : public Fitness
{
public:
    virtual ~DavesBouldin();

private:
    double maxDistance(Cluster *i, std::vector<Cluster *> clusters);
    double distance(Cluster *i, Cluster *j);

public:
    virtual DavesBouldin *clone() const;
    virtual bool operator>(const Fitness &other);
    virtual void updateValue(std::vector<Cluster *> clusters);
};
