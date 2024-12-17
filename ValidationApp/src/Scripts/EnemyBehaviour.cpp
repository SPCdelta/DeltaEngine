#include "EnemyBehaviour.hpp"

EnemyBehaviour::~EnemyBehaviour()
{
	sprite = nullptr;
	rigidbody = nullptr;
	delete _damageBehaviour;
	delete _aiBehaviour;
	playerPosition = nullptr;
}

void EnemyBehaviour::OnStart()
{
	switch (Enemy::StringToType(gameObject->GetTag()))
	{
		case EnemyType::Goblin:
			_enemy = std::make_unique<Goblin>(&gameObject->GetComponent<Transform>().position);
			break;
		case EnemyType::Skeleton:
			_enemy = std::make_unique<Skeleton>(&gameObject->GetComponent<Transform>().position);
			break;
		case EnemyType::Slime:
			_enemy = std::make_unique<Slime>(&gameObject->GetComponent<Transform>().position);
			break;
	}

	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);	
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();

	Math::Vector2* enemyPosition = &gameObject->GetComponent<Transform>().position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = new AIBehaviour(astar, enemyPosition, playerPosition, _enemy->GetRange(), _enemy->GetStep(), 2.0); // TODO speed is now 2.0
}

void EnemyBehaviour::OnUpdate()
{
	Math::Vector2* pos = &gameObject->GetComponent<Transform>().position;

	if (playerPosition)
		pos = _aiBehaviour->Update();

	if (pos != &gameObject->GetComponent<Transform>().position)
	{
		gameObject->GetComponent<Transform>().position.SetX(pos->GetX());
		gameObject->GetComponent<Transform>().position.SetY(pos->GetY());
	}
	
	_moveDirection = _aiBehaviour->GetDirection();
	if (sprite && sprite->GetAnimator() && _enemy->GetHealth() > 0)
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

	if (_damageBehaviour)
	{
		_damageBehaviour->Update(Time::GetDeltaTime());
		if (_damageBehaviour->GetDamage())
		{
			if (_enemy->GetHealth() > 0)
			{
				_damageBehaviour->TakeDamage();

				// TODO different amount of damage??
				// If need be, get colliding gameobj in takedamage() and decide then what the damage is
				// and return the damage to then use here in the sethealth() call
				_enemy->SetHealth(_enemy->GetHealth() - 1);

				_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
				_sfx->Play();
			}

			if (_enemy->GetHealth() <= 0)
			{
				_dead = true;
				Events::Event e{};
				onDeath.Dispatch(e);
			}
		}
	}
}

void EnemyBehaviour::SetPlayerPosition(Math::Vector2* pos)
{
	playerPosition = pos;
	_aiBehaviour->SetTargetPosition(playerPosition);
}

void EnemyBehaviour::SetDamageBehaviour(Rigidbody& rigid)
{
	_damageBehaviour = new DamageBehaviour(rigid, *sprite, {"projectile"});
}
