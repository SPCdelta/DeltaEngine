#include "PlayerBehaviour.hpp"
#include "../Items/Serializers/JsonItemSerializer.hpp"

void PlayerBehaviour::OnStart() 
{
	_player = std::make_unique<Player>();
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"goblin", "slime", "skeleton"});
	_pickUpBehaviour = new PickUpBehaviour(*rigidbody, *sprite, *_player);
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();
	
	//this->gameObject->GetCamera()->SetPosition(this->gameObject->transform->position);

	//_weapon = new Gun(this);
	//_weapon = new Bow(this);
	//onKeyPressed(Key::KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");

	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	InitHotbarKeybinds();
	// use consumables on right mb so that left mb is reserved for maybe throwing potions and the like?
	//onMouseButtonDown(MouseButton::Right, [this](Input& e) { ConsumeItem(); }, "Gameplay"); // TODO: fix inputmanager. For some reason this maps to KEY_02?
	onKeyPressed(KEY_V, [this](Input& e) { ConsumeItem(); }, "Gameplay"); // temporarily bind to KEY_V

	// Dit is voor testen van inventory en het opslaan/inladen van de inventory
	onKeyPressed(KEY_P, [this](Input& e) { LoadPlayer(); }, "Gameplay");
	onKeyPressed(KEY_O, [this](Input& e) { SavePlayer(); }, "Gameplay");
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	UpdateAttack(Time::GetDeltaTime());
	if (_playerInput.GetSpace())
	{
		_attacking = true;
		StartAttack();
	}
	bool attack = _attacking;

	_onFloor = _floorBehaviour->GetOnFloor();
	Math::Vector2 currentVelocity{ rigidbody->GetVelocity() };

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
				rigidbody->AddForce(_moveDirection * _moveSpeed, ForceMode::ACCELERATE);
			}

			currentVelocity = rigidbody->GetVelocity();
			rigidbody->AddForce(-currentVelocity * 1.0f, ForceMode::ACCELERATE);
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
	
	_damageBehaviour->Update(Time::GetDeltaTime());
	if (_damageBehaviour->GetDamage())
	{
		if (_player->GetHealth() > 0)
		{
			_damageBehaviour->TakeDamage();

			// TODO different amount of damage?? 
			// If need be, get colliding gameobj in takedamage() and decide then what the damage is 
			// and return the damage to then use here in the sethealth() call
			_player->SetHealth(_player->GetHealth() - 1);

			_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
			_sfx->Play();
		}
		
		if (_player->GetHealth() <= 0)
		{
			if (!deathSoundPlayed && !sprite->GetSheet()->PlayCustomAnimation("death"))
			{
				_sfx->SetClip("Assets\\Audio\\SFX\\Death.mp3");
				_sfx->Play();

				deathSoundPlayed = true;
				deathElapsedTime = 0.0f;
			}

			if (deathSoundPlayed)
			{
				deathElapsedTime += Time::GetDeltaTime();
				if (deathElapsedTime >= 1.0f)
					LoadScene("MainMenuScene"); 
			}
		}
	}

	if (sprite && sprite->GetAnimator() && _player->GetHealth() > 0)
	{
		// Attacking
		if (attack)
		{
			if (_weapon)
				_weapon->Use();
			else
				ThrowBoomerang();
		}
		
		// Walking
		if (_moveDirection.GetX() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::LEFT, false);
		else if (_moveDirection.GetX() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::RIGHT, false);
		else if (_moveDirection.GetY() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::DOWN, false);
		else if (_moveDirection.GetY() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::UP, false);

		// Idle
		else
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::NONE, false);
	}

	UpdateConsumables();

	this->gameObject->GetCamera()->SetPosition(this->gameObject->transform->position);
}

void PlayerBehaviour::UpdateAttack(float deltaTime)
{
	if (_attackTime > 0.0f)
		_attackTime -= deltaTime;
	else
		_attacking = false;
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

void PlayerBehaviour::ThrowBoomerang()
{
	// On Delay
	if (_boomerang)
		return;

	std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();
	_boomerang = boomerangObj->AddComponent<Boomerang>();
	Math::Vector2 throwDirection = transform->position.DirectionTo(gameObject->GetCamera()->ScreenToWorldPoint(_mouseX, _mouseY));

	_boomerang->Throw(gameObject, 15.0f, gameObject->transform->position, throwDirection);

	_boomerang->onFinish.Register([this, boomerangObj](Events::Event e)
	{ 
		Destroy(boomerangObj);
		_boomerang = nullptr;
	});
}

void PlayerBehaviour::LoadPlayer()
{
	Json::json loadedPlayer = _fileManager.Load("Assets\\Files\\player.json", "json");
	if (loadedPlayer.contains("player"))
	{
		_player->SetHealth(loadedPlayer["player"]["health"]);
		_player->SetCoins(loadedPlayer["player"]["coins"]);
		_player->SetShield(loadedPlayer["player"]["shield"]);
		_player->ResetInventory();

		if (loadedPlayer["player"].contains("inventory"))
		{
			for (size_t i = 0; i < loadedPlayer["player"]["inventory"].size(); ++i)
			{
				auto& itemData = loadedPlayer["player"]["inventory"][i];
				if (itemData.contains("type"))
				{
					_player->AddItemToInventory(PotionFactory::CreatePotion
					(
						itemData["type"],
						itemData["time"],
						itemData["sprite"],
						itemData["name"],
						itemData["value"]
					).release(), itemData["amount"]);
				}
				// TODO weapons?
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

	if (_player->GetInventorySize() > 0)
	{
		for (Uint8 i = 0; i < static_cast<int>(_player->GetInventorySize()); ++i)
		{
			auto& itemData = playerFile["player"]["inventory"][i];
			const std::optional<InventoryItem>& inventoryItem = _player->GetInventoryItem(i);

			if (!inventoryItem.has_value()) continue;

			itemData = JsonItemSerializer::Serialize(*inventoryItem->GetItem().Clone());
			itemData["amount"] = inventoryItem->GetAmount();
			// TODO weapons?
		}
	}
	
	_fileManager.Save("Assets\\Files\\player.json", "json", playerFile);
}
