#pragma once

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../BehaviourScript.hpp"

class UpdateSystem : public ecs::System<Transform, BehaviourScript*>
{
public:
	UpdateSystem(ecs::View<Transform, BehaviourScript*> view);
	~UpdateSystem();

	void Update();
};