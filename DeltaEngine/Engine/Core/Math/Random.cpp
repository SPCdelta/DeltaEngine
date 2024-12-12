#include "Random.hpp"

using namespace Math;

Random Random::instance;
std::random_device Random::rnd;

double Random::NextDouble(int min, int max) const
{
	if (min > max)
	{
		throw std::invalid_argument("Min should not be greater than max.");
	}

	std::uniform_real_distribution<double> dist(min, max);

	return dist(rnd);
}

double Random::NextDouble() const
{
	std::uniform_real_distribution<double> dist(0, 1);
	return dist(rnd);
}

bool Random::NextBool() const
{
	return NextInt(0, 1) == 1;
}