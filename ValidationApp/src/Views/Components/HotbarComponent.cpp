#include "HotbarComponent.hpp"

HotbarComponent::HotbarComponent(Scene& scene, Uint8 capacity, const std::string& fontPath, 
	const Math::Vector2& startPos, const Math::Vector2& scale, Player& player) : IView(scene, fontPath)
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
}
