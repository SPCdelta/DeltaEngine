#include "PlayerBehaviour.hpp"

#include "../Items/Serializers/JsonItemSerializer.hpp"
#include "../Classes/Weapons/WeaponFactory.hpp"
#include "../Utils/WeaponTypeUtils.hpp"

PlayerBehaviour::~PlayerBehaviour()
{
	sprite = nullptr;
	rigidbody = nullptr;
	_sfx = nullptr;

	delete _floorBehaviour;
	delete _damageBehaviour;
	delete _pickUpBehaviour;
	delete _weapon;
}

Player* PlayerBehaviour::GetPlayer() const
{
	return _player.get();
}

void PlayerBehaviour::OnStart() 
{
	_player = std::make_unique<Player>();
	sprite = &(transform->gameObject->GetComponent<Sprite>());
	rigidbody = &(transform->gameObject->GetComponent<Rigidbody>());
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"goblin", "slime", "skeleton_arrow", "boss"});
	_pickUpBehaviour = new PickUpBehaviour(*rigidbody, *sprite, *_player);
	
	if (transform->gameObject->HasComponent<Audio::SFXSource>())
	{
		_sfx = &(transform->gameObject->GetComponent<Audio::SFXSource>());
		_sfx->SetClip("taking_damage");
		_sfx->SetVolume(10);
	}

	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	InitHotbarKeybinds();

	onKeyPressed(KEY_ESCAPE, [this](Input& e) { LoadScene("MainMenuScene"); }, "Gameplay"); 
	onKeyPressed(KEY_V, [this](Input& e) { ConsumeItem(); }, "Gameplay"); 
	keyPressed(Key::KEY_SPACE, [this](Input& e)
	{
		_attacking = true;
	});

	// Physics Events
	rigidbody->onTriggerEnter.Register([this](Collider& collider)
	{ 
		if (collider.transform.gameObject && collider.transform.gameObject->GetTag() == "level_exit" && _player->GetHealth() > 0)
		{
			LevelExitBehaviour& exit = collider.transform.gameObject->GetComponent<LevelExitBehaviour>();
			SavePlayer();
			_pickUpBehaviour->ProcessDestructionQueue();

			if (!_scoreScreen)
			{
				_scoreScreen = std::make_unique<ScoreScreen>
				(
					*(transform->gameObject->_scene), 
					SCORE_SCREEN_FONT,
					Math::Vector2{0, 0}, 
					SCORE_SCREEN_SCALE, 
					"YOU WIN",
					WIN_MSG_COLOR, 
					_player->GetCoins()
				);
			}
		}
	});
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	if (_player->GetHealth() > 0 && _attacking && !_scoreScreen)
	{
		if (_weapon)
			_weapon->Use();

		_attacking = false;
	}

	if (_floorBehaviour)
		_onFloor = _floorBehaviour->GetOnFloor();
	else
		_onFloor = FloorType::NORMAL;
	
	Math::Vector2 currentVelocity{rigidbody->GetVelocity()};

#pragma region Floor Behaviour
	if (_moveDirection != Math::Vector2{0.0f, 0.0f} && _player->GetHealth() > 0 && !_scoreScreen)
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
				rigidbody->SetVelocity(_moveDirection * _player->GetSpeed());
				break;

			case FloorType::ICE:
				if (rigidbody->GetSpeed() < _player->GetSpeed())
					rigidbody->AddForce(_moveDirection * _player->GetSpeed(), ForceMode::ACCELERATE);

				currentVelocity = rigidbody->GetVelocity();
				rigidbody->AddForce(-currentVelocity * 1.0f,
									ForceMode::ACCELERATE);
				if (rigidbody->GetSpeed() <= 0.0f)
					rigidbody->SetVelocity(Math::Vector2(0.0f, 0.0f));
				break;

			case FloorType::MUD:			
				rigidbody->SetVelocity(_moveDirection * (_player->GetSpeed() * 0.5f));
				break;
		}
	}
	else
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
				rigidbody->SetVelocity({0.0f, 0.0f});
				break;

			case FloorType::ICE:
				rigidbody->AddForce(-currentVelocity * 1.0f, ForceMode::ACCELERATE);
				break;

			case FloorType::MUD:
				rigidbody->SetVelocity({0.0f, 0.0f});
				break;
		}
	}
#pragma endregion

#pragma region Damage Behaviour
	_damageBehaviour->Update(Time::GetDeltaTime());
	if (_damageBehaviour->GetDamage() && !_scoreScreen)
	{
		if (_player->GetHealth() > 0)
		{
			_player->TakeDamage(_damageBehaviour->TakeDamage());
			PlayHurtParticle();
			if (_sfx)
				_sfx->Play();
		}

		if (_player->GetHealth() <= 0)
		{
			if (!deathSoundPlayed && !sprite->GetSheet()->PlayCustomAnimation("death"))
			{
				if (_sfx)
				{
					_sfx->SetClip("death");
					_sfx->SetVolume(20);
					_sfx->Play();
				}

				deathSoundPlayed = true;
				deathElapsedTime = 0.0f;
			}

			if (deathSoundPlayed)
			{
				deathElapsedTime += Time::GetDeltaTime();
				if (deathElapsedTime >= 1.0f)
				{
					if (!_scoreScreen)
					{
						_scoreScreen = std::make_unique<ScoreScreen>
						(
							*(transform->gameObject->_scene), 
							SCORE_SCREEN_FONT,
							Math::Vector2{0, 0}, 
							SCORE_SCREEN_SCALE,
							DEATH_MSG,
							DEATH_MSG_COLOR,
							_player->GetCoins()
						);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Sprite Animation
	if (sprite && sprite->GetAnimator() && _player->GetHealth() > 0 && !_scoreScreen)
	{
		// Walking
		if (_moveDirection.GetX() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::LEFT, false);
		else if (_moveDirection.GetX() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::RIGHT, false);
		else if (_moveDirection.GetY() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::DOWN, false);
		else if (_moveDirection.GetY() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::UP, false);
		else // Idle
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::NONE, false);
	}
#pragma endregion

	UpdateConsumables();
	if (_weapon && !_scoreScreen) 
		_weapon->Update(Time::GetDeltaTime());

	this->transform->gameObject->GetCamera()->SetPosition(this->transform->position);
}

void PlayerBehaviour::SetWeapon(const std::string& weaponType)
{
	_weapon = WeaponFactory::CreateWeapon(weaponType, this).release();
}

void PlayerBehaviour::InitHotbarKeybinds()
{
	for (Uint8 i = 1; i <= 9; ++i)
		onKeyPressed(InputsEnum::toKey(std::to_string(i)), [this, i](Input& e) { _player->SetInventoryIndex(i-1); }, "Gameplay");
}

void PlayerBehaviour::ConsumeItem()
{
	auto& item = _player->GetCurrentInventoryItem();
	if (!item.has_value()) return;

    auto consumable = std::unique_ptr<ConsumableItem>(dynamic_cast<ConsumableItem*>(item->GetItem().Clone().release()));
	if (consumable)
	{
		consumable->Use(*_player.get());
		_player->RemoveItemFromInventory(*consumable.get(), 1);
		_activeConsumables.emplace_back(consumable.release());
	}
}

void PlayerBehaviour::UpdateConsumables()
{
	for (size_t i = 0; i < _activeConsumables.size(); ++i)
	{
		if (_activeConsumables[i]->Update())
			_activeConsumables.erase(_activeConsumables.begin() + i);
	}
}

void PlayerBehaviour::PlayHurtParticle() 
{
	if (transform->gameObject->HasComponent<ParticleEmitter>())
		transform->gameObject->RemoveComponent<ParticleEmitter>();
	
	transform->gameObject->AddComponent<ParticleEmitter>
	(
		ParticleEmitterConfiguration
		{
			{"particle_big", "particle_medium_1", "particle_medium_2", "particle_small", "particle_tiny"},
			{255, 0, 0, 255},
			{220, 0, 0, 255},

			1.0f, 25, 0.25f,

			2.0f, 2.0f,
			false,
			0.5f, 0.75f,
			0.5f, 0.75f,

			0.0f, 360.0f, 
			0.0f, 0.0f,

			0.05f, 0.05f
		}
	)->Start();
}

void PlayerBehaviour::LoadPlayer()
{
	Json::json loadedPlayer = _fileManager.Load("Assets\\Files\\player.json", "json");
	if (loadedPlayer.contains("player"))
	{
		_player->SetHealth(loadedPlayer["player"]["health"]);
		_player->SetCoins(loadedPlayer["player"]["coins"]);
		_player->SetShield(loadedPlayer["player"]["shield"]);

		_weapon = WeaponFactory::CreateWeapon(loadedPlayer["player"]["weapon"], this).release();
	
		if (loadedPlayer["player"].contains("inventory"))
		{
			_player->ResetInventory();
			for (size_t i = 0; i < loadedPlayer["player"]["inventory"].size(); ++i)
			{
				auto& itemData = loadedPlayer["player"]["inventory"][i];
				if (itemData.contains("type"))
				{
					auto potion = PotionFactory::CreatePotion
					(
						itemData["type"],
						itemData["time"],
						itemData["sprite"],
						itemData["name"],
						itemData["value"]
					);

					if (potion)
						_player->AddItemToInventory(potion.release(), itemData["amount"]);
				}
			}
		}
	}
}

void PlayerBehaviour::SavePlayer()
{
	Json::json playerFile;

	playerFile["player"]["health"] = _player->GetHealth();
	playerFile["player"]["shield"] = _player->GetShield();
	playerFile["player"]["coins"] = _player->GetCoins();
	playerFile["player"]["weapon"] = WeaponTypeUtils::ToString(_weapon->GetWeaponType());

	if (_player->GetInventorySize() > 0)
	{
		for (Uint8 i = 0; i < static_cast<int>(_player->GetInventoryCapacity()); ++i)
		{
			auto& itemData = playerFile["player"]["inventory"][i];
			const std::optional<InventoryItem>& inventoryItem = _player->GetInventoryItem(i);

			if (!inventoryItem.has_value()) continue;

			itemData = JsonItemSerializer::Serialize(*inventoryItem->GetItem().Clone());
			itemData["amount"] = inventoryItem->GetAmount();
		}
	}
	
	_fileManager.Save("Assets\\Files\\player.json", "json", playerFile);
}
