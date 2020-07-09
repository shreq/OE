#include "../include/point.hpp"
#include "../include/utils.hpp"

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

void Point::mutate()
{
    if (willMutate(centerMoveMutationRate))
    {
        x += getRandomGaussian();
        y += getRandomGaussian();
    }
}
