#pragma once

#include "Engine/Delta.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Items/Item.hpp"

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

	// bij het testen van inventory, dit aanzetten!

	//Inventory inventory;
	//Item _item1{"item 1"};
	//Item _item2{"item 2"};

};