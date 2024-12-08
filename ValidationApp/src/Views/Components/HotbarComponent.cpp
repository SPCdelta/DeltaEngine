#include "HotbarComponent.hpp"
#include <algorithm>

HotbarComponent::HotbarComponent(Scene& scene, Uint8 capacity, const std::string& fontName, 
	const Math::Vector2& startPos, const Math::Vector2& scale, Player& player) : IView(scene, fontName)
{
	auto pos = startPos;
	for (Uint8 i = 0; i < capacity; ++i)
	{
		auto slot = std::shared_ptr<GameObject>{ _scene.Instantiate({pos, 0.0f, scale }) };
		slot->AddComponent<Ui::Image>("hotbar_slot");

		auto* item = player.GetInventoryItem(i);
		auto itemIcon = std::shared_ptr<GameObject>{};
		std::string itemName = "";
		if (item)
		{
			itemIcon = std::shared_ptr<GameObject>{ _scene.Instantiate({ pos, 0.0f, scale }) };
			itemIcon->AddComponent<Ui::Image>(item->GetItem().GetSprite());
			itemName = item->GetItem().GetName();
		}
		_hotbar.emplace_back(slot, itemIcon, itemName);
		pos.AddX(scale.GetX());
	}
	player.AddInventoryObserver([this](const Item& item, int amount) { this->InventoryChanged(item, amount); });
}

void HotbarComponent::InventoryChanged(const Item& item, int amount)
{
	if (GetAvailableIndex() == UINT8_MAX)
	{
		return;
	}

	if (HasItem(item))
	{
		if (amount == 0) return;
		if (_hotbar[GetIndex(item)].amount + amount <= 0)
		{
			DeleteItem(item);
		}
		else 
		{
			IncrementItem(item, amount);
		}
	}
	else if (amount > 0)
	{
		AddItem(item, amount);
	}
}

Uint8 HotbarComponent::GetIndex(const Item& item) const
{
	for (Uint8 i = 0; i < _hotbar.size(); ++i)
	{
		if (_hotbar[i].itemName == item.GetName())
		{
			return i;
		}
	}
	throw std::exception("Could not find index of item.");
}

void HotbarComponent::AddItem(const Item& item, int amount)
{
	auto index = GetAvailableIndex();
	_hotbar[index].itemName = item.GetName();
	auto itemIcon = std::shared_ptr<GameObject>{ _scene.Instantiate({
		_hotbar[index].slot->transform->position,
		0.0f,
		_hotbar[index].slot->transform->scale }) };
	itemIcon->AddComponent<Ui::Image>(item.GetSprite());
	itemIcon->AddComponent<Ui::Text>(std::to_string(amount), _fontName, 20, DEFAULT_COLOR);
	_hotbar[index].itemIcon = itemIcon;
	_hotbar[index].amount += amount;
}

void HotbarComponent::IncrementItem(const Item& item, int amount)
{
	try
	{
		auto& slot = _hotbar[GetIndex(item)];
		slot.itemIcon->GetComponent<Ui::Text>().SetText(std::to_string(slot.amount + amount));
		slot.amount += amount;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void HotbarComponent::DeleteItem(const Item& item)
{
	auto index = GetIndex(item);
	auto& slot = _hotbar[index];
	slot.amount = 0;
	slot.itemName = "";
	_scene.DestroyObject(slot.itemIcon.get());
	SortHotbar(index);
}

void HotbarComponent::SortHotbar(Uint8 index)
{
	for (Uint8 i = index; i < _hotbar.size()-1; ++i)
	{
		std::swap(_hotbar[i], _hotbar[++i]);
	}
}


Uint8 HotbarComponent::GetAvailableIndex() const
{
	auto result = std::find_if(_hotbar.begin(), _hotbar.end(), [](const Slot& slot)
		{
			return slot.itemName.empty();
		});

	return static_cast<Uint8>(std::distance(_hotbar.begin(), result));
}

bool HotbarComponent::HasItem(const Item& item)
{
	for (auto slot : _hotbar)
	{
		if (slot.itemName == item.GetName())
		{
			return true;
		}
	}
	return false;
}
