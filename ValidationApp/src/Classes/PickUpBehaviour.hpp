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
				if ((collider.transform.gameObject->GetTag() == "item" || collider.transform.gameObject->GetTag() == "coin") && 
					collider.transform.gameObject->GetComponent<Sprite>().GetVisible())
				{
					if (collider.transform.gameObject->HasComponent<WorldItem>())
					{
						if (collider.transform.gameObject->GetTag() == "item")
						{
							WorldItem& item = collider.transform.gameObject->GetComponent<WorldItem>();
							_player.AddItemToInventory(item._item.release(), item._amount);
						}
						else // Coin
						{
							_player.AddCoins(1);
						}
						
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

		std::vector<std::shared_ptr<GameObject>> destructionQueue;

		void MarkForDestruction(std::shared_ptr<GameObject> obj)
		{
			destructionQueue.push_back(obj);
		}

		// TODO call upon this when leaving the scene
		void ProcessDestructionQueue()
		{
			for (auto& obj : destructionQueue)
				obj->Destroy();

			destructionQueue.clear();
		}
};