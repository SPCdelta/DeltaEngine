#include "PickUpBehaviour.hpp"

PickUpBehaviour::PickUpBehaviour(Rigidbody& rigidbody, Sprite& sprite, Player& player) 
	: _rigidbody{ rigidbody }, 
	  _sprite{ sprite }, 
	  _player{player}
{
	_rigidbody.onTriggerEnter.Register([this](Collider& collider)
	{ 
		if (collider.transform.gameObject && (collider.transform.gameObject->GetTag() == "item" || collider.transform.gameObject->GetTag() == "coin") && 
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

PickUpBehaviour::~PickUpBehaviour()
{
	// TODO unregister events
}

void PickUpBehaviour::MarkForDestruction(std::shared_ptr<GameObject> obj)
{
	destructionQueue.push_back(obj);
}

void PickUpBehaviour::ProcessDestructionQueue()
{
	for (auto& obj : destructionQueue)
		obj->Destroy();

	destructionQueue.clear();
}