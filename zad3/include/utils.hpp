#pragma once

/* #region settings */
extern bool elitism;

extern int centerRangeMin;
extern int centerRangeMax;

extern unsigned int centersCountMin;
extern unsigned int centersCountMax;

extern double centerMoveMutationRate;
extern double centerRemoveMutationRate;
extern double centerAddMutationRate;
/* #endregion settings */

int getRandomInt();
double getRandomDouble();
double getRandomGaussian();
bool willMutate(double mutationRate);
