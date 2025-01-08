#pragma once

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../Core/Despawner.hpp"

class DespawnSystem : public ecs::System<Transform, Despawner>
{
public:
	DespawnSystem(ecs::View<Transform, Despawner> view);

	void Update();
};