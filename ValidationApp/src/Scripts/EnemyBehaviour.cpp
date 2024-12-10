#include "EnemyBehaviour.hpp"

void EnemyBehaviour::OnStart()
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_damageBehaviour = new DamageBehaviour(*rigidbody, *sprite, "weapon");

	Math::Vector2* enemyPosition = &gameObject->GetComponent<Transform>().position;
	std::shared_ptr<AStarStrategy> astar = std::make_shared<AStarStrategy>();
	_aiBehaviour = new AIBehaviour(astar, enemyPosition, playerPosition);
}

void EnemyBehaviour::OnUpdate()
{
	_aiBehaviour->Update();

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