#include "../include/chromosome.hpp"
#include "../include/point.hpp"
#include "utils.cpp"
#include <iostream>

using namespace std;

Chromosome::Chromosome()
{
    centers = vector<Point *>();
    for (unsigned int i = 0; i < getRandomInt() % 10; i++)
    {
        centers.emplace_back(new Point());
    }
}

Chromosome::~Chromosome() {}

vector<Point *> Chromosome::getCenters()
{
    return centers;
}
