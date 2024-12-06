#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, "enemy");
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();
	_weapon = new Gun(this);
	//_weapon = new Bow(this);

	onKeyPressed(Key::KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");
	onMouseMove(
		[this](Input& e) 
		{ 
			_mouseX = e.mouseX;
			_mouseY = e.mouseY;
		}
	);
	keyPressed(Key::KEY_F,
		[this](Input& e)
		{ 
			if (_weapon)
			{
				_weapon->Use();
			}
		}
	);

	// Bij het testen van inventory, Dit aanzetten! 
	onKeyPressed(KEY_V, [this](Input& e) { _pot.Use(_player); }, "Gameplay");
	//onKeyPressed(KEY_V, [this](Input& e) { inventory.AddItem(_item1, 4); }, "Gameplay");
	//onKeyPressed(KEY_E, [this](Input& e) { inventory.PrintInventory(); }, "Gameplay");
	//onKeyPressed(KEY_L, [this](Input& e) { inventory.AddItem(_item2, 4); }, "Gameplay");
	//onKeyPressed(KEY_Q, [this](Input& e) { inventory.RemoveItem(_item1, 5);}, "Gameplay");
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
	//_pot.Update();

	if (_moveDirection != Math::Vector2{0.0f, 0.0f} && hp > 0)
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
		if (hp > 0)
		{
			_damageBehaviour->TakeDamage();
			std::cout << "player dying: " << hp << std::endl; 
			hp--;

			_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
			_sfx->Play();
		}
		
		if (hp <= 0) 
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

	if (sprite && sprite->GetAnimator() && hp > 0)
	{
		// Attacking
		if (attack)
		{
			// boomerang doesnt work quite yet, but when testing if an enemy (pokemonobj) takes damage from a weapon comment this in
			//ThrowBoomerang();

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
	// On Delay
	if (_boomerang)
		return;

	std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();
	_boomerang = boomerangObj->AddComponent<Boomerang>();
	Math::Vector2 throwDirection = transform->position.DirectionTo(gameObject->GetCamera()->ScreenToWorldPoint(_mouseX, _mouseY));

	_boomerang->Throw(gameObject, 15.0f, gameObject->transform->position, throwDirection);

	_boomerang->onFinish.Register(
		[this, boomerangObj](Events::Event e)
		{ 
			Destroy(boomerangObj);
			_boomerang = nullptr;
		}
	);
}
