#pragma once

#include <unordered_map>
#include <memory>
#include "Engine/Delta.hpp"
#include "../IView.hpp"
#include "../../Player.hpp"

struct Slot
{
	std::shared_ptr<GameObject> slot;
	std::shared_ptr<GameObject> itemIcon;
	std::string itemName;
};

class HotbarComponent : public IView
{
public:
	HotbarComponent(Scene& scene, Uint8 capacity, const std::string& fontPath, const Math::Vector2& startPos,
		const Math::Vector2& scale, Player& player);
private:
	// key = hotbar slot, value = item sprite
	std::vector<Slot> _hotbar;
};

