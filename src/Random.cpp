#include "Random.hpp"

Random::Random() : gen(rd())
{
}

int Random::randomInt(int min, int max)
{
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}