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
    Creature *rouletteSelection();
    Creature *randomCrossover(std::vector<Creature *> parents);

    void sortByFitness();
    std::vector<Creature *> selection(unsigned int numberOfSelected);
    std::vector<Creature *> generateOffspring();

public:
    void evolve(unsigned int generations);
};
