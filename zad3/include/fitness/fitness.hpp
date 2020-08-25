#pragma once
#include <vector>

class Cluster;

class Fitness
{
protected:
    long value;

public:
    virtual ~Fitness();

    long getValue() const;

    virtual bool operator>(const Fitness &other) = 0;
    virtual void updateValue(std::vector<Cluster *> clusters) = 0;
};
