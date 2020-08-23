#pragma once
#include <vector>
#include "./fitness.hpp"


class Cluster;

class WeightedFitness : Fitness
{
    long weight;
    Fitness * fitness;

public:
    WeightedFitness(Fitness * fitness, long weight);
    virtual ~WeightedFitness();
    long getWeight();

    bool operator>(const Fitness &other);
    bool operator>(WeightedFitness * other);
    void updateValue(std::vector<Cluster *> clusters);
};