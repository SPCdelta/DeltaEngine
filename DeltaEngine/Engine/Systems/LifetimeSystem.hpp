#pragma once

#include "../Ecs/Include.hpp"
#include "../Core/Time.hpp"

struct Lifetime
{
	float remaining;
};

class LifetimeSystem : ecs::System<Lifetime>
{
public:
	LifetimeSystem(ecs::Registry& reg);

	void Update();
};