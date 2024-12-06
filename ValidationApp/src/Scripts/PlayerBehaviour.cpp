#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, "enemy");
	_pickUpBehaviour = new PickUpBehaviour(*rigidbody, *sprite, _player);
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();

	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	// TODO dit is voor testen van inventory en het opslaan/inladen van de inventory
	onKeyPressed(KEY_X, [this](Input& e) { _player.AddItemToInventory(Item("item1", "none"), 4); },"Gameplay");
	onKeyPressed(KEY_C, [this](Input& e) { _player.AddItemToInventory(Item("item2", "none"), 4); }, "Gameplay");
	onKeyPressed(KEY_V, [this](Input& e) { _player.RemoveItemFromInventory("item1", 5);}, "Gameplay");	
	onKeyPressed(KEY_B, [this](Input& e) { _player.PrintInventory(); }, "Gameplay");	
	onKeyPressed(KEY_P, [this](Input& e) { LoadPlayer(); }, "Gameplay");
	onKeyPressed(KEY_O, [this](Input& e) { SavePlayer(); }, "Gameplay");
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	UpdateAttack(Time::GetDeltaTime());
	if (_playerInput.GetLeftClick())
	{
		_attacking = true;
		StartAttack();
	}
	bool attack = _attacking;

	_onFloor = _floorBehaviour->GetOnFloor();
	Math::Vector2 currentVelocity{ rigidbody->GetVelocity() };

	if (_moveDirection != Math::Vector2{0.0f, 0.0f} && _player.GetHealth() > 0)
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
			{
				if (!attack)
					rigidbody->SetVelocity(_moveDirection * _moveSpeed);
				else
					rigidbody->SetVelocity({0.0f, 0.0f});
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
				if (!attack)
					rigidbody->SetVelocity(_moveDirection * (_moveSpeed * 0.5f));
				else
					rigidbody->SetVelocity({0.0f, 0.0f});
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
		_player.GetHealth();
		if (_player.GetHealth() > 0)
		{
			_damageBehaviour->TakeDamage();

			// TODO different amount of damage?? 
			// If need be, get colliding gameobj in takedamage() and decide then what the damage is 
			// and return the damage to then use here in the sethealth() call
			_player.SetHealth(_player.GetHealth() - 1); 

			_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
			_sfx->Play();
		}
		
		if (_player.GetHealth() <= 0) 
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

	if (sprite && sprite->GetAnimator() && _player.GetHealth() > 0)
	{
		// Attacking
		if (attack)
		{
			ThrowBoomerang();

			if (sprite->GetSheet()->GetFacingDirection() == Direction::LEFT)
				sprite->GetSheet()->PlayCustomAnimation("attackLeft");
			else if (sprite->GetSheet()->GetFacingDirection() == Direction::RIGHT)
				sprite->GetSheet()->PlayCustomAnimation("attackRight");
			else if (sprite->GetSheet()->GetFacingDirection() == Direction::DOWN)
				sprite->GetSheet()->PlayCustomAnimation("attackDown");
			else if (sprite->GetSheet()->GetFacingDirection() == Direction::UP)
				sprite->GetSheet()->PlayCustomAnimation("attackUp");
		}
		
		// Walking
		if (_moveDirection.GetX() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::LEFT, attack);
		else if (_moveDirection.GetX() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::RIGHT, attack);
		else if (_moveDirection.GetY() < 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::DOWN, attack);
		else if (_moveDirection.GetY() > 0.0f)
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::UP, attack);

		// Idle
		else
			sprite->GetAnimator()->Play(sprite->GetSheet(), Direction::NONE, attack);
	}
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
	if (_boomerang)
		return;

	std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();
	_boomerang = boomerangObj->AddComponent<Boomerang>();
	boomerangObj->SetTag("weapon");

	Math::Vector2 mouseWorldPos{gameObject->GetCamera()->ScreenToWorldPoint(_mouseX, _mouseY)};
	Math::Vector2 throwDirection = (mouseWorldPos - gameObject->transform->position).GetNormalized();
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
		_player.SetHealth(loadedPlayer["player"]["health"]);
		_player.SetCoins(loadedPlayer["player"]["coins"]);
		_player.ResetInventory();

		if (loadedPlayer["player"].contains("inventory"))
		{
			for (size_t i = 0; i < loadedPlayer["player"]["inventory"].size(); ++i)
			{
				auto& itemData = loadedPlayer["player"]["inventory"][i];
				if (itemData.contains("type"))
				{
					PotionType type = static_cast<PotionType>(itemData["type"]);
					switch (type)
					{
						case PotionType::AttackUp:
						{
							AttackUpPotion potion = AttackUpPotion(itemData["time"], itemData["value"], itemData["name"], itemData["sprite"]);
							_player.AddItemToInventory(potion, itemData["amount"]);
						}
						break;
						case PotionType::Defense:
						{
							DefensePotion potion = DefensePotion(itemData["time"], itemData["value"], itemData["name"], itemData["sprite"]);
							_player.AddItemToInventory(potion, itemData["amount"]);
						}
						break;
						case PotionType::Healing:
						{
							HealingPotion potion = HealingPotion(itemData["time"], itemData["value"], itemData["name"], itemData["sprite"]);
							_player.AddItemToInventory(potion, itemData["amount"]);
						}
						break;
						case PotionType::Speed:
						{
							SpeedPotion potion = SpeedPotion(itemData["time"], itemData["value"], itemData["name"], itemData["sprite"]);
							_player.AddItemToInventory(potion, itemData["amount"]);
						}
						break;
					}
				}
				else
				{
					Item item = Item(itemData["name"], itemData["sprite"]); 
					_player.AddItemToInventory(item, itemData["amount"]);
				}

				// TODO weapons?
			}
		}
	}
}

void PlayerBehaviour::SavePlayer()
{
	Json::json playerFile;

	playerFile["player"]["health"] = _player.GetHealth();
	playerFile["player"]["coins"] = _player.GetCoins();

	if (_player.GetInventorySize() > 0)
	{
		for (size_t i = 0; i < _player.GetInventorySize(); ++ i)
		{
			auto& itemData = playerFile["player"]["inventory"][i];

			itemData["name"] = _player.GetInventoryItem(i)->GetItem().GetName();
			itemData["sprite"] = _player.GetInventoryItem(i)->GetItem().GetSprite();
			itemData["amount"] = _player.GetInventoryItem(i)->GetAmount();

			Potion* potion = dynamic_cast<Potion*>(&_player.GetInventoryItem(i)->GetItem());
			if (potion)
			{
				itemData["type"] = static_cast<int>(potion->GetType());
				itemData["value"] = potion->GetValue();
				itemData["time"] = potion->GetTime();
			}

			// TODO weapons?
		}
	}
	
	_fileManager.Save("Assets\\Files\\player.json", "json", playerFile);
}
