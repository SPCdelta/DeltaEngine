#pragma once

#include "../BehaviourScript.hpp"
#include "../Ecs/Include.hpp"
#include "../Transform.hpp"

struct AStarWalkable
{
	bool walkable;
	Math::Vector2 position;
};

class AStarSystem : public ecs::System<Transform, AStarWalkable>
{
public:
	AStarSystem(ecs::Registry& reg);

	void GetWalkableTiles(std::vector<Transform*>& tiles, std::vector<Transform*>& walls);
};