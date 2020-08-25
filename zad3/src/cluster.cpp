#include "../include/cluster.hpp"
#include "../include/point.hpp"

using namespace std;

Cluster::Cluster(Point *center, vector<Point *> points) : center(center), points(points) {}

Cluster::~Cluster() {}

Point *Cluster::getCenter()
{
    return center;
}

vector<Point *> Cluster::getPoints()
{
    return points;
}

bool Cluster::isEmpty()
{
    return points.size() == 0;
}
