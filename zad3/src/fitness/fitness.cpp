#include "../../include/fitness/fitness.hpp"
#include <vector>

using namespace std;

Fitness::~Fitness() {}

long Fitness::getValue() const
{
    return value;
}
