#include "PlayerBehaviour.hpp"
#include "../Items/Serializers/JsonItemSerializer.hpp"
#include "../Classes/Weapons/WeaponFactory.hpp"
#include "../Utils/WeaponTypeUtils.hpp"

void PlayerBehaviour::OnStart()
{
	_player = std::make_unique<Player>();
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"goblin", "slime", "skeleton_arrow", "boss"});
	_pickUpBehaviour = new PickUpBehaviour(*rigidbody, *sprite, *_player);
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();

	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	InitHotbarKeybinds();
	// use consumables on right mb so that left mb is reserved for maybe throwing potions and the like?
	//onMouseButtonDown(MouseButton::Right, [this](Input& e) { ConsumeItem(); }, "Gameplay"); // TODO: fix inputmanager. For some reason this maps to KEY_02?
	onKeyPressed(KEY_V, [this](Input& e) { ConsumeItem(); }, "Gameplay"); // temporarily bind to KEY_V

	keyPressed(Key::KEY_SPACE, [this](Input& e)
	{
		_attacking = true;
	});

	// Physics Events
	rigidbody->onTriggerEnter.Register([this](Collider& collider)
	{ 
		// Player checks this so we could for example have a requirement on this exit (like 10 kills or 20 coins)
		if (collider.transform.gameObject->GetTag() == "level_exit" && _player->GetHealth() > 0)
		{
			LevelExitBehaviour& exit = collider.transform.gameObject->GetComponent<LevelExitBehaviour>();
			SavePlayer();
			exit.Use();
		}
	});
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	if (_player->GetHealth() > 0 && _attacking)
	{
		if (_weapon)
			_weapon->Use();

		_attacking = false;
	}

	_onFloor = _floorBehaviour->GetOnFloor();
	Math::Vector2 currentVelocity{rigidbody->GetVelocity()};

#pragma region Floor Behaviour
	if (_moveDirection != Math::Vector2{0.0f, 0.0f} && _player->GetHealth() > 0)
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
			{
				rigidbody->SetVelocity(_moveDirection * _moveSpeed);
			}
			break;

			case FloorType::ICE:
				if (rigidbody->GetSpeed() < _moveSpeed)
				{
					rigidbody->AddForce(_moveDirection * _moveSpeed,
										ForceMode::ACCELERATE);
				}

				currentVelocity = rigidbody->GetVelocity();
				rigidbody->AddForce(-currentVelocity * 1.0f,
									ForceMode::ACCELERATE);
				if (rigidbody->GetSpeed() <= 0.0f)
				{
					rigidbody->SetVelocity(Math::Vector2(0.0f, 0.0f));
				}
				break;

			case FloorType::MUD:
			{
				rigidbody->SetVelocity(_moveDirection * (_moveSpeed * 0.5f));
			}
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
				rigidbody->AddForce(-currentVelocity * 1.0f,
									ForceMode::ACCELERATE);
				break;
			case FloorType::MUD:
				rigidbody->SetVelocity({0.0f, 0.0f});
				break;
		}
	}
#pragma endregion

#pragma region Damage Behaviour
	_damageBehaviour->Update(Time::GetDeltaTime());
	if (_damageBehaviour->GetDamage())
	{
		if (_player->GetHealth() > 0)
		{
			_player->TakeDamage(_damageBehaviour->TakeDamage());
			_sfx->SetClip("taking_damage");
			PlayHurtParticle();
			_sfx->Play();
		}

		if (_player->GetHealth() <= 0)
		{
			if (!deathSoundPlayed &&
				!sprite->GetSheet()->PlayCustomAnimation("death"))
			{
				_sfx->SetClip("death");
				_sfx->Play();

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
						_scoreScreen = std::make_unique<ScoreScreen>(
							*gameObject->_scene, SCORE_SCREEN_FONT,
							Math::Vector2{0, 0}, SCORE_SCREEN_SCALE,
							DEATH_MSG,
							DEATH_MSG_COLOR,
							_player->GetCoins());
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Sprite Animation
	if (sprite && sprite->GetAnimator() && _player->GetHealth() > 0)
	{
		// Walking
		if (_moveDirection.GetX() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::LEFT,
										false);
		else if (_moveDirection.GetX() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::RIGHT,
										false);
		else if (_moveDirection.GetY() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::DOWN,
										false);
		else if (_moveDirection.GetY() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::UP,
										false);

		// Idle
		else
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::NONE,
										false);
	}
#pragma endregion

	UpdateConsumables();
	_weapon->Update(Time::GetDeltaTime());

	this->gameObject->GetCamera()->SetPosition(
		this->gameObject->transform->position);
}

void PlayerBehaviour::SetWeapon(const std::string& weaponType)
{
	_weapon = WeaponFactory::CreateWeapon(weaponType, this).release();
}

void PlayerBehaviour::InitHotbarKeybinds()
{
	for (Uint8 i = 1; i <= 9; ++i)
	{
		onKeyPressed(InputsEnum::toKey(std::to_string(i)), [this, i](Input& e) { _player->SetInventoryIndex(i-1); }, "Gameplay");
	}
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
		{
			_activeConsumables.erase(_activeConsumables.begin() + i);
		}
	}
}

void PlayerBehaviour::PlayHurtParticle() 
{
	if (gameObject->HasComponent<ParticleEmitter>())
	{
		gameObject->RemoveComponent<ParticleEmitter>();
	}

	gameObject->AddComponent<ParticleEmitter>(
		ParticleEmitterConfiguration{
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

			0.25f, 0.25f
		})
	->Start();
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
					auto potion = PotionFactory::CreatePotion(
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
