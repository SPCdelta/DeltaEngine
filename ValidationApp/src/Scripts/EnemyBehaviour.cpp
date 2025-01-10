#include "EnemyBehaviour.hpp"
#include "../Classes/DamageBehaviour.hpp"

EnemyBehaviour::~EnemyBehaviour()
{
	sprite = nullptr;
	rigidbody = nullptr;
	playerPosition = nullptr;
	_damageBehaviour = nullptr;
	player = nullptr;
}

void EnemyBehaviour::OnStart()
{
	switch (Enemy::StringToType(transform->gameObject->GetTag()))
	{
		case EnemyType::Goblin:
			_enemy = std::make_unique<Goblin>(&transform->gameObject->GetComponent<Transform>().position);
			break;
		case EnemyType::Skeleton:
			_enemy = std::make_unique<Skeleton>(&transform->gameObject->GetComponent<Transform>().position, transform->gameObject->transformRef);
			break;
		case EnemyType::Slime:
			_enemy = std::make_unique<Slime>(&transform->gameObject->GetComponent<Transform>().position);
			break;
		case EnemyType::Boss:
		default:
			_enemy = std::make_unique<Slime>(&transform->gameObject->GetComponent<Transform>().position, true, 3.5f, 100, 20, 30, 5);
			break;
	}

	sprite = &transform->gameObject->GetComponent<Sprite>();
	rigidbody = &transform->gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);	
	_sfx = std::make_unique<Audio::SFXSource>(transform->gameObject->GetComponent<Audio::SFXSource>());

	Math::Vector2* enemyPosition = &transform->position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = std::make_unique<AIBehaviour>(astar, transform, playerPosition, _enemy->GetRange(), _enemy->GetStep(), _enemy->GetSpeed()); 

	_damageObj = Instantiate(*transform);
	_damageObj->AddComponent<BoxCollider>();
	_damageObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
	_damageObj->AddComponent<EnemyHitboxBehaviour>()->SetEnemyPosition(&transform->position) ;
	SetDamageBehaviour(_damageObj->GetComponent<Rigidbody>());
}

void EnemyBehaviour::OnUpdate()
{
	if (!transform || !transform->gameObject || !transform->gameObject->HasComponent<Transform>() || _enemy->IsDead())
		return ;

	Transform* pos = &transform->gameObject->GetComponent<Transform>();

	if (playerPosition)
	{
		pos = _aiBehaviour->Update();
		_enemy->Update(*playerPosition, _sfx.get());
	}
		
	if (pos != &transform->gameObject->GetComponent<Transform>())
	{
		transform->gameObject->GetComponent<Transform>().position.SetX(pos->position.GetX());
		transform->gameObject->GetComponent<Transform>().position.SetY(pos->position.GetY());
	}
	
	_moveDirection = _aiBehaviour->GetDirection();
	UpdateAnimation();

	if (_damageBehaviour)
	{
		_damageBehaviour->Update(Time::GetDeltaTime());
		if (_damageBehaviour->GetDamage())
		{
			if (_enemy && _enemy->GetHealth() > 0 && _sfx)
			{
				_enemy->SetHealth(_enemy->GetHealth() - _damageBehaviour->TakeDamage());
				_sfx->SetClip("taking_damage");
				_sfx->Play();
			}

			if (_enemy && _enemy->GetHealth() <= 0)
			{
				if (player && Enemy::StringToType(transform->gameObject->GetTag()) == EnemyType::Boss)
					player->AddCoins(1000);
				else
					player->AddCoins(10);

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

void EnemyBehaviour::SetPlayer(Transform* pos, Player* play)
{
	player = play;
	playerPosition = pos;
	_aiBehaviour->SetTargetPosition(playerPosition);
}

void EnemyBehaviour::SetDamageBehaviour(Rigidbody& rigid)
{
	_damageBehaviour = std::make_unique<DamageBehaviour>(rigid, *sprite, std::initializer_list<std::string>{"projectile"});
}

void EnemyBehaviour::OnDeath()
{
	if (_damageObj)
		_damageObj->Destroy();
	if (transform->gameObject && transform->gameObject->HasComponent<Sprite>())
		transform->gameObject->GetComponent<Sprite>().SetVisible(false);
	transform->gameObject->Destroy();
}
