#pragma once
#include <vector>
#include <map>

class Point;
class Creature;

class Clusterer
{
    std::vector<Point *> data;
    std::vector<Creature *> creatures;
    unsigned int generation;

public:
    Clusterer(std::vector<Point *> data, unsigned int populationSize);
    virtual ~Clusterer();

    std::vector<Creature *> getCreatures();
    unsigned int getGeneration();

private:
    Creature *rouletteSelection();
    Creature *randomCrossover(std::vector<Creature *> parents);

    std::vector<Creature *> sortByFitness(std::vector<Creature *> creatures);
    std::vector<Creature *> selection(unsigned int numberOfSelected);
    std::vector<Creature *> generateOffspring();

public:
    void evolve(unsigned int generations);
    std::map<Point *, std::vector<Point *>> cluster();
};
