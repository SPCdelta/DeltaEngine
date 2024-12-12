#include "EnemyBehaviour.hpp"

void EnemyBehaviour::OnStart()
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"weapon"});

	Math::Vector2* enemyPosition = &gameObject->GetComponent<Transform>().position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = new AIBehaviour(astar, enemyPosition, playerPosition, 2.0);
}

void EnemyBehaviour::OnUpdate()
{
	if (playerPosition)
		_aiBehaviour->Update();

	_moveDirection = _aiBehaviour->GetDirection();
	if (sprite && sprite->GetAnimator()/* && _player->GetHealth() > 0*/)
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

	_damageBehaviour->Update(Time::GetDeltaTime());
	if (_damageBehaviour->GetDamage())
	{
		if (hp > 0)
		{
			_damageBehaviour->TakeDamage();
			std::cout << "enemy dying: " << hp << std::endl; 
			hp--;
		}

		if (hp <= 0)
		{
			std::cout << "i died!" << std::endl;
			sprite->SetColor(Rendering::Color(0.0f, 0.0f, 0.0f, 1.0f)); 
		}
	}
}

void EnemyBehaviour::SetPlayerPosition(Math::Vector2* pos)
{
	playerPosition = pos;
	_aiBehaviour->SetTargetPosition(playerPosition);
}
