#ifndef UTILS_CPP
#define UTILS_CPP
#pragma once

#include <chrono>
#include <random>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_real_distribution<double> distribution(0.0, 1.0);

/* #region mutation rates */
double mutationRate = 0.3;
/* #endregion mutation rates */

int getRandomInt()
{
    return generator();
}

double getRandomDouble(){
    return distribution(generator);
}

bool willMutate(double mutationRate)
{
    return (getRandomDouble() < mutationRate);
}

#endif // UTILS_CPP
