#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP
#pragma once

#include <vector>

class Point;

class Chromosome
{
    std::vector<Point *> centers;

public:
    Chromosome();
    virtual ~Chromosome();

    std::vector<Point *> getCenters();
};

#endif // CHROMOSOME_HPP
