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
		int NextInt(int min, int max) const;
		double NextDouble(int min, int max) const;
		double NextDouble() const;
		bool NextBool() const;
	private:
		static Random instance;
		static std::random_device rnd;
		Random() {}
	};
}

