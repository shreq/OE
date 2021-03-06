#pragma once
#include <vector>
#include "./fitness.hpp"

class Cluster;
class WeightedFitness;

class ComplexFitness : public Fitness
{
    std::vector<WeightedFitness *> fitnessList;

public:
    ComplexFitness();
    virtual ~ComplexFitness();

    void add(Fitness *fitness, double weight);
    virtual ComplexFitness *clone() const;
    virtual bool operator>(const Fitness &other);
    bool operator>(const ComplexFitness &other);
    virtual void updateValue(std::vector<Cluster *> clusters);
};
