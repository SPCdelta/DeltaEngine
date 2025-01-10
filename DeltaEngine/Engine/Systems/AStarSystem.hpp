#pragma once

#include "../BehaviourScript.hpp"
#include "../Ecs/Include.hpp"
#include "../Transform.hpp"

struct AStarWalkable
{
	bool walkable;
};

class AStarSystem : public ecs::System<Transform, AStarWalkable>
{
public:
	AStarSystem(ecs::Registry& reg)
		: ecs::System<Transform, AStarWalkable>(reg)
	{

	}

	void GetWalkableTiles(std::vector<Transform*>& tiles)
	{
		RefreshView();
		for (ecs::EntityId entityId : _view)
		{
			if (_view.get<AStarWalkable>(entityId).walkable)
				tiles.push_back(&_view.get<Transform>(entityId));
		}
	}
};