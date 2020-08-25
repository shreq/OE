#include "../../include/fitness/fitness.hpp"
#include <vector>

using namespace std;

Fitness::~Fitness() {}

double Fitness::getValue() const
{
    return value;
}
