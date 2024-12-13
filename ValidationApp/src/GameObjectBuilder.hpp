#pragma once

#include "Engine/Delta.hpp"
#include "Items/WorldItem.hpp"

class GameObjectBuilder
{
public:
	std::shared_ptr<GameObject> BuildWorldItem(const WorldItem wItem) const; 
};