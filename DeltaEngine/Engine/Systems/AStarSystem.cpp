#include "AStarSystem.hpp"

AStarSystem::AStarSystem(ecs::Registry& reg)
	: ecs::System<Transform, AStarWalkable>(reg)
{

}

void AStarSystem::GetWalkableTiles(std::vector<Transform*>& tiles, std::vector<Transform*>& walls)
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		if (_view.get<AStarWalkable>(entityId).walkable)
			tiles.push_back(&_view.get<Transform>(entityId));
		else if (!_view.get<AStarWalkable>(entityId).walkable)
			walls.push_back(&_view.get<Transform>(entityId));
	}
}