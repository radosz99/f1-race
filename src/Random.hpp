#pragma once
#include <random>


class Random
{
private:
	std::random_device rd;
	std::mt19937 gen;

public:
	Random();
	int randomInt(int min, int max);

};