#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"
#include "../Items/WorldItem.hpp"

class PickUpBehaviour
{
   public:
		PickUpBehaviour(Rigidbody& rigidbody, Sprite& sprite, Player& player) : _rigidbody{ rigidbody }, _sprite{ sprite }, _player{player}
		{
			_rigidbody.onTriggerEnter.Register([this](Collider& collider)
			{ 
				if (collider.transform.gameObject->GetTag() == "item" && collider.transform.gameObject->GetComponent<Sprite>().GetVisible())
				{
					if (collider.transform.gameObject->HasComponent<WorldItem>())
					{
						WorldItem item = collider.transform.gameObject->GetComponent<WorldItem>();
						_player.AddItemToInventory(item._item, item._amount);

						std::cout << "player picked up " << item._amount << " " << item._item.GetName() <<std::endl;

						collider.transform.gameObject->GetComponent<Sprite>().SetVisible(false);
						MarkForDestruction(collider.transform.gameObject);
					}
				}
			});
		}

		~PickUpBehaviour()
		{
			// TODO unregister events
		}

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;
		Player& _player;

		std::vector<GameObject*> destructionQueue;

		void MarkForDestruction(GameObject* obj)
		{
			destructionQueue.push_back(obj);
		}

		// TODO call upon this when leaving the scene
		void ProcessDestructionQueue()
		{
			for (auto& obj : destructionQueue)
				obj->Destroy(obj);

			destructionQueue.clear();
		}
};