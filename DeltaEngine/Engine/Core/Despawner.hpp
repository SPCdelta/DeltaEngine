#pragma once

#include "../GameObject.hpp"
#include "Time.hpp"

class DespawnSystem;

class Despawner
{
public:
	Despawner(float despawnAfter);

	friend class DespawnSystem;

private:
	float _timer;
};