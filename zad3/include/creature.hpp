#pragma once

#include <vector>

class Point;

class Creature
{
    std::vector<Point *> centers;
    double fitness;

    inline void removeCenter();
    inline void addCenter();

public:
    Creature();
    Creature(std::vector<Point *> centers);
    virtual ~Creature();

    std::vector<Point *> getCenters();
    double getFitness();

    void updateFitness();
    void mutate();
};
