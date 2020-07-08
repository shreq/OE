#pragma once
#include <vector>

class Point;

class Creature
{
    std::vector<Point *> centers;
    double fitness;

public:
    Creature();
    Creature(std::vector<Point *> centers);
    virtual ~Creature();

    std::vector<Point *> getCenters();
    double getFitness();

private:
    inline void removeCenter();
    inline void addCenter();

public:
    void updateFitness();
    void mutate();
};
