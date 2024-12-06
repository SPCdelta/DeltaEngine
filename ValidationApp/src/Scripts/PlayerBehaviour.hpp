#pragma once

#include "Engine/Delta.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Items/Item.hpp"
#include "../Player.hpp"
#include "../Items/Potions/AttackUpPotion.hpp"

#include "../Classes/DamageBehaviour.hpp"
#include "../Classes/FloorBehaviour.hpp"
#include "../Classes/PlayerInput.hpp"

#include "Boomerang.hpp"
#include "../Classes/Weapons/Gun.hpp"
#include "../Classes/Weapons/Bow.hpp"

#include "../Items/Potions/SpeedPotion.hpp"
#include "../Items/Potions/DefensePotion.hpp"
#include "../Items/Potions/HealingPotion.hpp"

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	~PlayerBehaviour()
	{
		sprite = nullptr;
		rigidbody = nullptr;
		_sfx = nullptr;

		delete _floorBehaviour;
		delete _damageBehaviour;
	}

	void ThrowBoomerang();

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

	void UpdateAttack(float deltaTime);

private:
	FloorBehaviour* _floorBehaviour{nullptr};
	DamageBehaviour* _damageBehaviour{nullptr};
	PlayerInput _playerInput{ this };

	// Weapons
	Boomerang* _boomerang = nullptr;
	Weapon* _weapon = nullptr;

	// Audio
	Audio::SFXSource* _sfx;

	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	int _mouseX = 0;
	int _mouseY = 0;

	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	FloorType _onFloor{ FloorType::NORMAL };


	Player _player{25, 10, 10, 95};
	HealingPotion _pot{10, 10, "healingpotion"};

	//Inventory inventory;
	//Item _item1{"item 1"};
	//Item _item2{"item 2"};

	bool _attacking{false};
	float _attackTime{0.0f};
	const float _attackDuration = 0.4f;	
	void StartAttack() { _attackTime = _attackDuration; }

	int hp{20};

	float deathElapsedTime = 0.0f;
	bool deathSoundPlayed = false;
};