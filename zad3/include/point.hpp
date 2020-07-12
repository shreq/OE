#pragma once
#include <string>

class Point
{
    double x;
    double y;

public:
    Point();
    Point(double x, double y);
    virtual ~Point();

    double getX();
    double getY();
    std::string toString();
    std::string toString(std::string separator);

    void mutate();
    double euclideanDistance(Point *point);
};
