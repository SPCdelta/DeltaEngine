#pragma once

#include "Engine/Delta.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Items/Item.hpp"
#include "../Player.hpp"
#include "../Items/Potions/AttackUpPotion.hpp"

enum class FloorType
{
	NORMAL = 0,
	ICE = 1,
	MUD = 2,
};

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

private:
	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;
	int _sensorCount = 0;
	FloorType _onFloor{ FloorType::NORMAL };
	Player _player{25, 10, 10, 100};
	AttackUpPotion _attackuppot{10, 5, "attackUppotion", _player};

	// bij het testen van inventory, dit aanzetten!

	//Inventory inventory;
	//Item _item1{"item 1"};
	//Item _item2{"item 2"};

};