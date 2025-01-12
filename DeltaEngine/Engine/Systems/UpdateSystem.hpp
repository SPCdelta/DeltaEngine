#pragma once

#include "../Ecs/Include.hpp"
#include "../Transform.hpp"
#include "../BehaviourScript.hpp"

class BehaviourSystem : public ecs::System<std::unique_ptr<BehaviourScript>>
{
public:
	BehaviourSystem(ecs::Registry& reg);

	void Update();
};