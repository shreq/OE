#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class WeightedFitness : public Fitness
{
    Fitness *fitness;
    double weight;

public:
    WeightedFitness(Fitness *fitness, double weight);
    virtual ~WeightedFitness();

    double getWeight();

    virtual WeightedFitness *clone() const;
    virtual bool operator>(const Fitness &other);
    virtual bool operator>(WeightedFitness *other);
    virtual void updateValue(std::vector<Cluster *> clusters);
};
