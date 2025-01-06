#pragma once

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
		const Math::Vector2& slotScale, Player& player);
	void InventoryChanged(const Item& item, int amount);
	void InventoryIndexChanged(Uint8 index);
	const Math::Vector2& GetSize() const override;
private:
	Uint8 GetIndex(const Item& item) const;
	void AddItem(const Item& item, int amount);
	void IncrementItem(const Item& item, int amount);
	void DeleteItem(const Item& item);
	Uint8 GetAvailableIndex() const;
	bool HasItem(const Item& item);
	void Subscribe();
	std::vector<Slot> _hotbar;
	Uint8 _index = 0;
	Player& _player;
	const float TEXT_SCALE = 0.2f;
	const Rendering::Color TEXT_COLOR = {255, 255, 255, 255};
	const std::string HOTBAR_SLOT_SPRITENAME = "hotbar_slot";
	const std::string ACTIVE_HOTBAR_SLOT_SPRITENAME = "active_slot";
	Math::Vector2 _tempScale;
};

