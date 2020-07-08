#include "../include/utils.hpp"
#include <chrono>
#include <random>

/* #region settings */
bool elitism = true;

int centerRangeMin = -1000;
int centerRangeMax = 1000;

unsigned int centersCountMin = 2;
unsigned int centersCountMax = 10;

double centerMoveMutationRate = 0.3;
double centerRemoveMutationRate = 0.1;
double centerAddMutationRate = 0.1;
/* #endregion settings */

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_real_distribution<double> uniform_distribution(0.0, 1.0);
std::normal_distribution<double> normal_distribution(0, 10);

int getRandomInt()
{
    return generator();
}

double getRandomDouble()
{
    return uniform_distribution(generator);
}

double getRandomGaussian()
{
    return normal_distribution(generator);
}

bool willMutate(double mutationRate)
{
    return (getRandomDouble() < mutationRate);
}
