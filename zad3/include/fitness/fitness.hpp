#pragma once
#include <vector>

class Cluster;

class Fitness
{
protected:
    double value = 0.0;

public:
    virtual ~Fitness();

    double getValue() const;

    virtual Fitness *clone() const = 0;
    virtual bool operator>(const Fitness &other) = 0;
    virtual void updateValue(std::vector<Cluster *> clusters) = 0;
};
