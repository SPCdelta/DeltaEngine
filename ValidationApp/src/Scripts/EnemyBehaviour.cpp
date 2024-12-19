#include "EnemyBehaviour.hpp"
#include "../Classes/DamageBehaviour.hpp"

EnemyBehaviour::~EnemyBehaviour()
{
	sprite = nullptr;
	rigidbody = nullptr;
	playerPosition = nullptr;
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
		case EnemyType::Boss:
		default:
			_enemy = std::make_unique<Slime>(&gameObject->GetComponent<Transform>().position, true, 2.5f, 100, 25, 30, 5);
			break;
	}

	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);	
	_sfx = std::make_unique<Audio::SFXSource>(gameObject->GetComponent<Audio::SFXSource>());

	Math::Vector2* enemyPosition = &transform->position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = std::make_unique<AIBehaviour>(astar, transform, playerPosition, _enemy->GetRange(), _enemy->GetStep(), _enemy->GetSpeed()); 

	_damageObj = Instantiate(*transform);
	_damageObj->AddComponent<BoxCollider>();
	_damageObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	_damageObj->AddComponent<EnemyHitboxBehaviour>()->SetEnemyPosition(&transform->position) ;
	SetDamageBehaviour(_damageObj->GetComponent<Rigidbody>());

	// TODO smaller collider
	// TODO try and fix arrows
	// TODO try and fix mem leaks
}

void EnemyBehaviour::OnUpdate()
{
	Transform* pos = &gameObject->GetComponent<Transform>();

	if (playerPosition)
	{
		pos = _aiBehaviour->Update();
		_enemy->Update(*playerPosition, _sfx.get());
	}
		
	if (pos != &gameObject->GetComponent<Transform>())
	{
		gameObject->GetComponent<Transform>().position.SetX(pos->position.GetX());
		gameObject->GetComponent<Transform>().position.SetY(pos->position.GetY());
	}
	
	_moveDirection = _aiBehaviour->GetDirection();
	UpdateAnimation();

	if (_damageBehaviour)
	{
		_damageBehaviour->Update(Time::GetDeltaTime());
		if (_damageBehaviour->GetDamage())
		{
			if (_enemy->GetHealth() > 0 && _sfx)
			{
				_enemy->SetHealth(_enemy->GetHealth() - _damageBehaviour->TakeDamage());
				_sfx->SetClip("Assets\\Audio\\SFX\\Taking_damage.mp3");
				_sfx->Play();
			}

			if (_enemy->GetHealth() <= 0)
			{
				_enemy->Die(_sfx.get());
				OnDeath();
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

void EnemyBehaviour::SetPlayerPosition(Transform* pos)
{
	playerPosition = pos;
	_aiBehaviour->SetTargetPosition(playerPosition);
}

void EnemyBehaviour::SetDamageBehaviour(Rigidbody& rigid)
{
	_damageBehaviour = std::make_unique<DamageBehaviour>(rigid, *sprite, std::initializer_list<std::string>{"projectile"});
}

void EnemyBehaviour::OnDeath()
{
	Destroy(_damageObj);
	gameObject->GetComponent<Sprite>().SetVisible(false);
	gameObject->Destroy(gameObject);
}
