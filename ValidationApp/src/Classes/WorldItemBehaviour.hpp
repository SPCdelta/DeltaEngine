#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"

class WorldItemBehaviour
{
   public:
		WorldItemBehaviour(Rigidbody& rigidbody, Sprite& sprite, Player& player) : _rigidbody{ rigidbody }, _sprite{ sprite }, _player{player}
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

		~WorldItemBehaviour()
		{
			// TODO unregister events
		}

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;
		Player& _player;
};