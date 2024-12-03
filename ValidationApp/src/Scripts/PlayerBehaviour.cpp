#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite);

	InputManager::onKeyPressed(KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");
	InputManager::onMouseMove(
		[this](Input& e) 
		{ 
			_mouseX = e.mouseX;
			_mouseY = e.mouseY;
		}
	);
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();

	_playerInput.UpdateAttack(Time::GetDeltaTime());
	bool attack = _playerInput.GetLeftClick();

	_onFloor = _floorBehaviour->GetOnFloor();
	Math::Vector2 currentVelocity{ rigidbody->GetVelocity() };

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

			case FloorType::ICE: // TODO attack ?
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
			std::cout << hp << std::endl;
			hp--;

			auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
			sfx.SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
			sfx.Play();
		}
		
		if (hp <= 0) 
		{
			if (!deathSoundPlayed && !sprite->GetSheet()->PlayCustomAnimation("death"))
			{
				auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
				sfx.SetClip("Assets\\Audio\\SFX\\Death.mp3");
				sfx.Play();

				deathSoundPlayed = true;
				deathElapsedTime = 0.0f;
			}

			if (deathSoundPlayed)
			{
				deathElapsedTime += Time::GetDeltaTime();
				if (deathElapsedTime >= 1.0f)
					LoadScene("MainMenuScene"); // TODO death screen
			}
		}
		
	}

	if (sprite && sprite->GetAnimator() && hp > 0)
	{
		// Attacking
		if (attack)
		{
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

void PlayerBehaviour::ThrowBoomerang() 
{
	std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();
	Boomerang* boomerang = boomerangObj->AddComponent<Boomerang>();

	Math::Vector2 mouseWorldPos{gameObject->GetCamera()->ScreenToWorldPoint(_mouseX, _mouseY)};
	Math::Vector2 throwDirection = (mouseWorldPos - gameObject->transform->position).GetNormalized();
	boomerang->Throw(gameObject, 5.0f, gameObject->transform->position, throwDirection);
}
