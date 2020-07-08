#pragma once

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

    void mutate();
};
