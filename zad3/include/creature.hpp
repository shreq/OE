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

    bool operator==(const Creature &creature);

private:
    void removeCenter();
    void addCenter();

public:
    void updateFitness();
    void mutate();
};
