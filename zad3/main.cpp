#include <iostream>
#include "src/point.cpp"
#include "src/chromosome.cpp"

using namespace std;

int main()
{
	Chromosome chromosome;
	for (auto center : chromosome.getCenters())
	{
		cout << center->getX() << ' ' << center->getY() << '\n';
	}
	return 0;
}
