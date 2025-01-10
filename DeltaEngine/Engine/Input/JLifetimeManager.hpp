#pragma once

#include "JInputEntry.hpp"

class JInputLifetimeManager
{
public:
	void Add(JInputLifetime* lifetime) { _inputs.push_back(lifetime); }

	~JInputLifetimeManager()
	{
		for (JInputLifetime* input : _inputs)
		{
			delete input;
		}
		_inputs.clear();
	}

private:
	std::vector<JInputLifetime*> _inputs{};
};