#pragma once
#include <string>
#include <vector>

class Point;
class Cluster;

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
double averageDistance(Point *point, std::vector<Point *> otherPoints);
double averageDistance(Cluster *cluster);
double distanceOfCenters(Cluster *first, Cluster *second);

std::vector<Point *> readCsv(std::string filepath);
