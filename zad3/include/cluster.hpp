#pragma once
#include <vector>

class Point;

class Cluster
{
    Point *center;
    std::vector<Point *> points;

public:
    Cluster(Point *center, std::vector<Point *> points);
    virtual ~Cluster();

    Point *getCenter();
    std::vector<Point *> getPoints();
};
