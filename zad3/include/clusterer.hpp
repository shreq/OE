#pragma once

#include <vector>

class Creature;

class Clusterer
{
    std::vector<Creature *> creatures;

public:
    Clusterer(unsigned int populationSize);
    virtual ~Clusterer();

    std::vector<Creature *> getCreatures();

    void updateFitness();
    Creature *selection();
    Creature *crossover(Creature *creatureA, Creature *creatureB);
    void mutate();
    void evolve();
};
