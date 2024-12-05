#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"

class PickUpBehaviour
{
   public:
		PickUpBehaviour(Rigidbody& rigidbody, Sprite& sprite, Player& player) : _rigidbody{ rigidbody }, _sprite{ sprite }, _player{player}
		{
			_rigidbody.onTriggerEnter.Register([this](Collider& collider)
			{ 
				if (collider.transform.gameObject->GetTag() == "item")
				{
					// TODO player pick up item
					// _player.AddItemToInventory(_item1, 4);

					
				}
			});
		}

		~PickUpBehaviour()
		{
			// TODO unregister events
		}

		/*void Update(float deltaTime)
		{

		}*/

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;
		Player& _player;
};