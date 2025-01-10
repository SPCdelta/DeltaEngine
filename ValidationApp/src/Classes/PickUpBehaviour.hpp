#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"
#include "../Items/WorldItem.hpp"

class PickUpBehaviour
{
public:
	PickUpBehaviour(Rigidbody& rigidbody, Sprite& sprite, Player& player);
	~PickUpBehaviour();

	void ProcessDestructionQueue();

private:
	Rigidbody& _rigidbody;
	Sprite& _sprite;
	Player& _player;

	std::vector<GameObject*> destructionQueue;

	void MarkForDestruction(GameObject* obj);
};