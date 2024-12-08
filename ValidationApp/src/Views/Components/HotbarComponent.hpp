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
	int amount;
};

class HotbarComponent : public IView
{
public:
	HotbarComponent(Scene& scene, Uint8 capacity, const std::string& fontName, const Math::Vector2& startPos,
		const Math::Vector2& scale, Player& player);
	void InventoryChanged(const Item& item, int amount);
private:
	Uint8 GetIndex(const Item& item) const;
	void AddItem(const Item& item, int amount);
	void IncrementItem(const Item& item, int amount);
	void DeleteItem(const Item& item);
	void SortHotbar(Uint8 index);
	Uint8 GetAvailableIndex() const;
	bool HasItem(const Item& item);
	std::vector<Slot> _hotbar;
};

