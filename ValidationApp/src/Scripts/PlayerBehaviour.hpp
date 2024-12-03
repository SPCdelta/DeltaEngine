#pragma once

#include "Engine/Delta.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Items/Item.hpp"
#include "../Player.hpp"
#include "../Items/Potions/AttackUpPotion.hpp"

#include "../Classes/FloorBehaviour.hpp"
#include "../Classes/PlayerInput.hpp"
#include "Boomerang.hpp"
#include "../Items/Potions/SpeedPotion.hpp"
#include "../Items/Potions/DefensePotion.hpp"
#include "../Items/Potions/HealingPotion.hpp"

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void ThrowBoomerang();

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

private:
	FloorBehaviour* _floorBehaviour = nullptr;
	PlayerInput _playerInput{ this };

	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	int _mouseX = 0;
	int _mouseY = 0;

	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	FloorType _onFloor{ FloorType::NORMAL };

	Player _player{25, 10, 10, 25};
	DefensePotion _pot{10, 10, "speedpotion"};

	//Inventory inventory;
	//Item _item1{"item 1"};
	//Item _item2{"item 2"};

};