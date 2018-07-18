#include <cstdlib>
#include <ctime>
#include "Random.h"

void Random::setSeed(int seed)
{
	srand((seed < 0) ? time(NULL) : seed);
}

int Random::getInt(int size)
{
	return rand() % size;
}