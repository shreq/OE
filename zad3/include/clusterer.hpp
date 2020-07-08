#pragma once
#include <vector>

class Creature;

class Clusterer
{
    std::vector<Creature *> creatures;
    unsigned int generation;

public:
    Clusterer(unsigned int populationSize);
    virtual ~Clusterer();

    std::vector<Creature *> getCreatures();
    unsigned int getGeneration();

private:
    void updateFitness();
    Creature *selection();
    Creature *crossover(Creature *creatureA, Creature *creatureB);
    void mutate();

public:
    void evolve();
};
