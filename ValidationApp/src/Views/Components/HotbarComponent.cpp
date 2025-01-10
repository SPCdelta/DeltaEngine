#include "HotbarComponent.hpp"
#include <algorithm>

HotbarComponent::HotbarComponent(Scene& scene, Uint8 capacity, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& slotScale, Player* player) 
	: IView(scene, fontName, startPos, slotScale), 
	  _player{player}
{
	auto pos = startPos;
	for (Uint8 i = 0; i < capacity; ++i)
	{
		auto slot = std::shared_ptr<GameObject>{ _scene.Instantiate({pos, 0.0f, slotScale }) };
		slot->AddComponent<Ui::Image>(HOTBAR_SLOT_SPRITENAME);
		slot->AddComponent<Ui::Button>()->SetOnLeftMouseClick([i, &player]() -> void { player->SetInventoryIndex(i); }, "Hotbar");

		auto itemIcon = std::shared_ptr<GameObject>{};
		std::string itemName = "";

		/*auto& item = player->GetInventoryItem(i);
		if (item.has_value())
		{
			itemIcon = std::shared_ptr<GameObject>{ _scene.Instantiate({ pos, 0.0f, slotScale }) };
			itemIcon->AddComponent<Ui::Image>(item->GetItem()->GetSprite());
			itemName = item->GetItem()->GetName();
		}*/ // TODO from merge?

		_hotbar.emplace_back(slot, itemIcon, itemName);
		pos.AddX(slotScale.GetX());
	}
	_hotbar[_index].slot->GetComponent<Ui::Image>().SetSprite(ACTIVE_HOTBAR_SLOT_SPRITENAME);

	// TODO from merge \/ ??
	for (int i = 0; i < player->GetInventorySize(); i ++)
	{
		auto& item = player->GetInventoryItem(i);
		AddItem(*item->GetItem(), player->GetInventoryItem(i)->GetAmount());
	}

	Subscribe();
	{
		float width = _hotbar.size() * _scale.GetX();
		float height = _scale.GetY();
		_tempScale = {  width, height };
	}
}

void HotbarComponent::InventoryChanged(const Item& item, int amount)
{
	if (GetAvailableIndex() == UINT8_MAX)
		return;

	if (HasItem(item))
	{
		if (amount == 0) return;

		if (_hotbar[GetIndex(item)].amount + amount <= 0)
			DeleteItem(item);
		else 
			IncrementItem(item, amount);
	}
	else if (amount > 0)
	{
		AddItem(item, amount);
	}
}

void HotbarComponent::InventoryIndexChanged(Uint8 index)
{
	_hotbar[_index].slot->GetComponent<Ui::Image>().SetSprite(HOTBAR_SLOT_SPRITENAME);
	_index = index;
	_hotbar[_index].slot->GetComponent<Ui::Image>().SetSprite(ACTIVE_HOTBAR_SLOT_SPRITENAME);
}

const Math::Vector2& HotbarComponent::GetSize() const
{
	return _tempScale;
} 

Uint8 HotbarComponent::GetIndex(const Item& item) const
{
	for (Uint8 i = 0; i < _hotbar.size(); ++i)
	{
		if (_hotbar[i].itemName == item.GetName())
			return i;
	}
	throw std::exception("Could not find index of item.");
}

void HotbarComponent::AddItem(const Item& item, int amount)
{
	auto index = GetAvailableIndex();
	_hotbar[index].itemName = item.GetName();

	auto itemIcon = std::shared_ptr<GameObject>
	{ 
		_scene.Instantiate(
		{
			_hotbar[index].slot->transform->position,
			0.0f,
			_hotbar[index].slot->transform->scale 
		}) 
	};

	itemIcon->AddComponent<Ui::Image>(item.GetSprite());
	itemIcon->AddComponent<Ui::Text>(std::to_string(amount), _fontName, static_cast<int>(_scale.Magnitude() * TEXT_SCALE), DEFAULT_COLOR);

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
			return true;
	}
	return false;
}

void HotbarComponent::Subscribe()
{
	_player->AddInventoryObserver([this](const Item& item, int amount) { this->InventoryChanged(item, amount); });
	_player->AddInventoryIndexObserver([this](Uint8 index) { this->InventoryIndexChanged(index); });
}
