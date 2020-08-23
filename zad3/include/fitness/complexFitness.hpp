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
    
private:
    void add(Fitness * fitness, long weight);

public:
    bool operator>(const ComplexFitness &other);
    void updateValue(std::vector<Cluster *> clusters);
};