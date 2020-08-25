#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;

class WeightedFitness : public Fitness
{
    Fitness *fitness;
    long weight;

public:
    WeightedFitness(Fitness *fitness, long weight);
    virtual ~WeightedFitness();

    long getWeight();

    bool operator>(const Fitness &other);
    bool operator>(WeightedFitness *other);
    void updateValue(std::vector<Cluster *> clusters);
};
