#ifndef POINT_HPP
#define POINT_HPP
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
};

#endif // POINT_HPP
