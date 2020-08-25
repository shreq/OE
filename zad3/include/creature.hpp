#pragma once
#include <vector>
#include <map>

class Point;
class Cluster;
class Fitness;

class Creature
{
    std::vector<Point *> centers;
    std::vector<Point *> data;
    Fitness *fitness;

public:
    Creature(std::vector<Point *> data, Fitness *fitnessStrategy);
    Creature(std::vector<Point *> centers, std::vector<Point *> data, Fitness *fitnessStrategy);
    virtual ~Creature();

    std::vector<Point *> getCenters();
    Fitness *getFitness();
    double getFitnessValue();

    bool operator==(const Creature &creature);

private:
    void removeCenter();
    void addCenter();
    std::vector<Cluster *> calculateClusters();

public:
    void updateFitness();
    void mutate();
};
