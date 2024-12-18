#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	_player = std::make_unique<Player>();
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"goblin", "slime", "skeleton_arrow"});
	_pickUpBehaviour = new PickUpBehaviour(*rigidbody, *sprite, *_player);
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();
	
	//this->gameObject->GetCamera()->SetPosition(this->gameObject->transform->position);

	//_weapon = new Gun(this);
	_weapon = new Bow(this);
	//onKeyPressed(Key::KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");

	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	// Dit is voor testen van inventory en het opslaan/inladen van de inventory
	onKeyPressed(KEY_X, [this](Input& e) { _player->AddItemToInventory(Item("item1", "cyanPotion"), 4); },"Gameplay");
	//onKeyPressed(KEY_C, [this](Input& e) { _player->AddItemToInventory(Item("item2", "none"), 4); }, "Gameplay"); stukkie wukkie
	onKeyPressed(KEY_V, [this](Input& e) { _player->RemoveItemFromInventory(Item("item1", "cyanPotion"), 5);}, "Gameplay");
	onKeyPressed(KEY_B, [this](Input& e) { _player->PrintInventory(); }, "Gameplay");
	onKeyPressed(KEY_Y, [this](Input& e) { _player->SetShield(69); }, "Gameplay");
	onKeyPressed(KEY_Q, [this](Input& e) { _player->SetCoins(69); }, "Gameplay");
	onKeyPressed(KEY_P, [this](Input& e) { LoadPlayer(); }, "Gameplay");
	onKeyPressed(KEY_O, [this](Input& e) { SavePlayer(); }, "Gameplay");

	keyPressed(Key::KEY_SPACE, [this](Input& e)
	{
		_attacking = true;
		StartAttack();
	});

	// Physics Events
	rigidbody->onTriggerEnter.Register([this](Collider& collider)
	{ 
		// Player checks this so we could for example have a requirement on this exit (like 10 kills or 20 coins)
		if (collider.transform.gameObject->GetTag() == "level_exit")
		{
			LevelExitBehaviour& exit = collider.transform.gameObject->GetComponent<LevelExitBehaviour>();
			exit.Use();
		}
	});
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	UpdateAttack(Time::GetDeltaTime());
	if (_attacking)
	{
		if (_weapon)
			_weapon->Use();
		else
			ThrowBoomerang();
	}

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
			_player->SetHealth(_player->GetHealth() - _damageBehaviour->TakeDamage());
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

	this->gameObject->GetCamera()->SetPosition(this->gameObject->transform->position);
}

void PlayerBehaviour::UpdateAttack(float deltaTime)
{
	if (_attackTime > 0.0f)
		_attackTime -= deltaTime;
	else
		_attacking = false;
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

		if (!loadedPlayer["player"]["weapon"].contains("boomerang"))
		{
			if (loadedPlayer["player"]["weapon"].contains("gun"))
				_weapon = new Gun(this);
			else
				_weapon = new Bow(this);
		}

		_player->ResetInventory();
		if (loadedPlayer["player"].contains("inventory"))
		{
			for (size_t i = 0; i < loadedPlayer["player"]["inventory"].size(); ++i)
			{
				auto& itemData = loadedPlayer["player"]["inventory"][i];
				if (itemData.contains("type"))
				{
					PotionType type = static_cast<PotionType>(itemData["type"]);
					auto potion = PotionFactory::CreatePotion(type, itemData);
					_player->AddItemToInventory(*potion, itemData["amount"]);
				}
				else
				{
					Item item = Item(itemData["name"], itemData["sprite"]); 
					_player->AddItemToInventory(item, itemData["amount"]);
				}
			}
		}
	}
}

void PlayerBehaviour::SavePlayer()
{
	Json::json playerFile;

	playerFile["player"]["health"] = _player->GetHealth();
	playerFile["player"]["coins"] = _player->GetCoins();
	if (_weapon)
	{
		if (auto gun = dynamic_cast<Gun*>(_weapon))
			playerFile["player"]["weapon"] = "gun";
		else
			playerFile["player"]["weapon"] = "bow";
	}		
	else
	{
		playerFile["player"]["weapon"] = "boomerang";
	}

	if (_player->GetInventorySize() > 0)
	{
		for (int i = 0; i < static_cast<int>(_player->GetInventorySize()); ++ i)
		{
			auto& itemData = playerFile["player"]["inventory"][i];
			auto& inventoryItem = _player->GetInventoryItem(i)->GetItem();

			itemData["name"] = inventoryItem.GetName();
			itemData["sprite"] = inventoryItem.GetSprite();
			itemData["amount"] = _player->GetInventoryItem(i)->GetAmount();

			if (auto potion = dynamic_cast<Potion*>(&inventoryItem))
			{
				itemData["type"] = static_cast<int>(potion->GetType());
				itemData["value"] = potion->GetValue();
				itemData["time"] = potion->GetTime();
			}
		}
	}
	
	_fileManager.Save("Assets\\Files\\player.json", "json", playerFile);
}
