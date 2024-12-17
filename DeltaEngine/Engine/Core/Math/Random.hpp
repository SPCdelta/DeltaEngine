#pragma once
#include <random>

namespace Math
{
class Random
{
   public:
	static Random& get_instance() { return instance; }
	Random(const Random&) = delete;
	Random(Random&&) = delete;
	Random& operator=(const Random&) = delete;
	Random& operator=(Random&&) = delete;

	static float NextFloat(float min, float max)
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

	static int NextInt(int min, int max)
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

	double NextDouble(int min, int max) const;
	double NextDouble() const;

	bool NextBool() const;

   private:
	static Random instance;
	static std::random_device rnd;
	Random() {}
};
}

