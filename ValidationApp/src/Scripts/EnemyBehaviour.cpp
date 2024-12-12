#include "EnemyBehaviour.hpp"

void EnemyBehaviour::OnStart()
{
	_enemy = std::make_unique<Goblin>(&gameObject->GetComponent<Transform>().position, 5); // TODO, not always a goblin
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, {"projectile"});
	_sfx = &gameObject->GetComponent<Audio::SFXSource>();

	Math::Vector2* enemyPosition = &gameObject->GetComponent<Transform>().position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = new AIBehaviour(astar, enemyPosition, playerPosition, 2.0);
}

void EnemyBehaviour::OnUpdate()
{
	if (playerPosition)
		_aiBehaviour->Update();

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

		if (_enemy->GetHealth() <= 0) // TODO
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
