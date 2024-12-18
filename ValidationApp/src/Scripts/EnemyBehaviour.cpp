#include "EnemyBehaviour.hpp"
#include "../Classes/DamageBehaviour.hpp"

EnemyBehaviour::~EnemyBehaviour()
{
	sprite = nullptr;
	rigidbody = nullptr;
	playerPosition = nullptr;
	_sfx = nullptr;
	_damageBehaviour = nullptr;
}

void EnemyBehaviour::OnStart()
{
	switch (Enemy::StringToType(gameObject->GetTag()))
	{
		case EnemyType::Goblin:
			_enemy = std::make_unique<Goblin>(&gameObject->GetComponent<Transform>().position);
			break;
		case EnemyType::Skeleton:
			_enemy = std::make_unique<Skeleton>(&gameObject->GetComponent<Transform>().position, gameObject);
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
	_aiBehaviour = std::make_unique<AIBehaviour>(astar, enemyPosition, playerPosition, _enemy->GetRange(), _enemy->GetStep(), _enemy->GetSpeed()); 
}

void EnemyBehaviour::OnUpdate()
{
	Math::Vector2* pos = &gameObject->GetComponent<Transform>().position;

	if (playerPosition)
	{
		pos = _aiBehaviour->Update();
		_enemy->Update(*playerPosition, _sfx);
	}
		
	if (pos != &gameObject->GetComponent<Transform>().position)
	{
		gameObject->GetComponent<Transform>().position.SetX(pos->GetX());
		gameObject->GetComponent<Transform>().position.SetY(pos->GetY());
	}
	
	_moveDirection = _aiBehaviour->GetDirection();
	UpdateAnimation();

	if (_damageBehaviour)
	{
		_damageBehaviour->Update(Time::GetDeltaTime());
		if (_damageBehaviour->GetDamage())
		{
			if (_enemy->GetHealth() > 0)
			{
				_enemy->SetHealth(_enemy->GetHealth() - _damageBehaviour->TakeDamage());
				_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
				_sfx->Play();
			}

			if (_enemy->GetHealth() <= 0)
			{
				_dead = true;
				_enemy->Die();
				Events::Event e{};
				onDeath.Dispatch(e);
				return;
			}
		}
	}
}

void EnemyBehaviour::UpdateAnimation()
{
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
}

void EnemyBehaviour::SetPlayerPosition(Math::Vector2* pos)
{
	playerPosition = pos;
	_aiBehaviour->SetTargetPosition(playerPosition);
}

void EnemyBehaviour::SetDamageBehaviour(Rigidbody& rigid)
{
	_damageBehaviour = std::make_unique<DamageBehaviour>(rigid, *sprite, std::initializer_list<std::string>{"projectile"});
}
