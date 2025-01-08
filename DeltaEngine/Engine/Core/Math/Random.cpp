#include "Random.hpp"

using namespace Math;

Random Random::instance;
std::random_device Random::rnd;

Random::Random()
{

}

float Math::Random::NextFloat(float min, float max)
{
	if (min > max)
	{
		float tempMin = min;
		min = max;
		max = tempMin;
	}

	std::uniform_real_distribution<float> dist(min, max);
	return dist(instance.rnd);
}

int Math::Random::NextInt(int min, int max)
{
	if (min > max)
	{
		int tempMin = min;
		min = max;
		max = tempMin;
	}

	std::uniform_int_distribution<int> dist(min, max);
	return dist(instance.rnd);
}

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