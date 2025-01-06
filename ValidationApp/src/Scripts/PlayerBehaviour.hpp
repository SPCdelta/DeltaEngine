#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"

#include "../Classes/DamageBehaviour.hpp"
#include "../Classes/FloorBehaviour.hpp"
#include "../Classes/PickUpBehaviour.hpp"
#include "../Classes/PlayerInput.hpp"
#include "Boomerang.hpp"
#include "../Classes/Weapons/Gun.hpp"
#include "../Classes/Weapons/Bow.hpp"

#include "../Views/ScoreScreen.hpp"

#include "../Items/Potions/PotionFactory.hpp"

#include "Level/LevelExitBehaviour.hpp"

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
		delete _pickUpBehaviour;
		delete _weapon;
		delete _boomerang;
	}

	void ThrowBoomerang();

	void LoadPlayer();
	void SavePlayer();

	Player* GetPlayer() const { return _player.get(); }

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

	void UpdateAttack(float deltaTime);

private:
	FloorBehaviour* _floorBehaviour{nullptr};
	DamageBehaviour* _damageBehaviour{nullptr};
	PickUpBehaviour* _pickUpBehaviour{nullptr};
	PlayerInput _playerInput{ this };

	// Files
	FileManager _fileManager;

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

	std::unique_ptr<Player> _player;
	std::vector<std::unique_ptr<ConsumableItem>> _activeConsumables;

	std::unique_ptr<ScoreScreen> _scoreScreen;
	const std::string DEATH_MSG = "You died";
	const Math::Vector2 SCORE_SCREEN_SCALE = {500, 500};
	const Rendering::Color DEATH_MSG_COLOR = {255, 0, 0, 255};
	const std::string SCORE_SCREEN_FONT = "goblin";

	void InitHotbarKeybinds();
	void ConsumeItem();
	void UpdateConsumables();

	bool _attacking{false};
	float _attackTime{0.0f};
	const float _attackDuration = 0.4f;	
	void StartAttack() { _attackTime = _attackDuration; }

	float deathElapsedTime = 0.0f;
	bool deathSoundPlayed = false;
};