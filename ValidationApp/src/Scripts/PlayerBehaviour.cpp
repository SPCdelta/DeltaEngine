#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, "enemy");
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();

	// TODO
	//onKeyPressed(KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");

	onKeyPressed(KEY_P, [this](Input& e) { LoadPlayer(); }, "Gameplay");
	onKeyPressed(KEY_P, [this](Input& e) { SavePlayer(); }, "Gameplay");
	
	onMouseMove([this](Input& e) 
	{ 
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});

	// TODO
	// Bij het testen van inventory, Dit aanzetten! 
	//onKeyPressed(KEY_V, [this](Input& e) { _pot.Use(_player); }, "Gameplay");
	//onKeyPressed(KEY_V, [this](Input& e) { _player.AddItemToInventory(_item1, 4); }, "Gameplay");
	//onKeyPressed(KEY_E, [this](Input& e) { inventory.PrintInventory(); }, "Gameplay");
	//onKeyPressed(KEY_L, [this](Input& e) { _player.AddItemToInventory(_item2, 4); }, "Gameplay");
	//onKeyPressed(KEY_Q, [this](Input& e) { _player.RemoveItemFromInventory(_item1, 5);}, "Gameplay");
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

	// TODO
	//_pot.Update();

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
			// TODO
			// boomerang doesnt work quite yet, but when testing if an enemy (pokemonobj) takes damage from a weapon comment this in
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
	// TODO
	Json::json loadedInventory = _fileManager.Load("Assets\\Files\\player.json", "json");
	/*if (loadTiles.contains("tiles"))
	{
		for (size_t i = 0; i < loadTiles["tiles"].size(); ++i)
		{
			auto& tile = loadTiles["tiles"][i];
			if (tile.contains("transform"))
			{
				TransformDTO transformDTO
				{
					static_cast<float>(tile["transform"]["position"]["x"]),
					static_cast<float>(tile["transform"]["position"]["y"]),
					static_cast<float>(tile["transform"]["rotation"]),
					static_cast<float>(tile["transform"]["scale"]["x"]),
					static_cast<float>(tile["transform"]["scale"]["y"])
				};

				// TODO
				std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();;
				std::shared_ptr<GameObject> obj{ Instantiate(transformDTO.ToTransform()) }

				if (tile.contains("sprite"))
				{
					std::string spriteName = tile["sprite"]["name"];
					Layer layer = static_cast<Layer>(tile["layer"]);
					obj->AddComponent<Sprite>(spriteName.c_str())->SetLayer(layer);
				}

				if (tile.contains("boxCollider"))
				{
					bool isTrigger = tile["boxCollider"]["isTrigger"];
					obj->AddComponent<BoxCollider>()->SetTrigger(isTrigger);
				}

				if (tile.contains("tag"))
				{
					obj->SetTag(tile["tag"]);
				}
			}
		}
	}*/
}

void PlayerBehaviour::SavePlayer()
{
	// TODO
	Json::json playerFile;

	playerFile["player"]["health"] = _player.GetHealth();

	for (size_t i = 0; i < _player.GetInventorySize(); ++ i)
	{
		auto& itemData = playerFile["player"]["inventory"][i];

		itemData["name"] = _player.GetInventoryItem(i)->GetItem().GetName();
		itemData["sprite"] = _player.GetInventoryItem(i)->GetItem().GetSprite();
		itemData["amount"] = _player.GetInventoryItem(i)->GetAmount();

		Potion* potion = dynamic_cast<Potion*>(&_player.GetInventoryItem(i)->GetItem());
		if (potion)
		{
			itemData["type"] = potion->GetType(); // static_cast<int>(sprite.GetLayer());
			itemData["value"] = potion->GetValue();
			itemData["time"] = potion->GetTime();
		}

		/*tileJson["transform"]["position"]["x"] = tiles[i]->GetComponent<Transform>().position.GetX();
		tileJson["transform"]["position"]["y"] = tiles[i]->GetComponent<Transform>().position.GetY();
		tileJson["transform"]["rotation"] = tiles[i]->GetComponent<Transform>().rotation;
		tileJson["transform"]["scale"]["x"] = tiles[i]->GetComponent<Transform>().scale.GetX();
		tileJson["transform"]["scale"]["y"] = tiles[i]->GetComponent<Transform>().scale.GetY();

		tileJson["tag"] = tiles[i]->GetTag();

		if (tiles[i]->HasComponent<Sprite>())
		{
			const auto& sprite = tiles[i]->GetComponent<Sprite>();
			tileJson["sprite"]["name"] = sprite.GetSprite();  
			tileJson["layer"] = static_cast<int>(sprite.GetLayer());
		}
					
		if (tiles[i]->HasComponent<BoxCollider>())
		{
			const auto& collider = tiles[i]->GetComponent<BoxCollider>();
			tileJson["boxCollider"]["isTrigger"] = collider.IsTrigger();
		}*/
	}

	_fileManager.Save("Assets\\Files\\player.json", "json", playerFile);
}
