#include "../include/point.hpp"
#include "../include/utils.hpp"
#include <cmath>

using namespace std;

Point::Point() : x(getRandomGaussian()), y(getRandomGaussian()) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() {}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
}

string Point::toString()
{
    return to_string(x) + ", " + to_string(y);
}

string Point::toString(string separator)
{
    return to_string(x) + separator + to_string(y);
}

void Point::mutate()
{
    if (willMutate(centerMoveMutationRate))
    {
        x += getRandomGaussian();
        y += getRandomGaussian();
    }
}

double Point::euclideanDistance(Point *point)
{
    double x_diff = x - point->getX();
    double y_diff = y - point->getY();
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}
