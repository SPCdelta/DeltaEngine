#include "EnemyHitboxBehaviour.hpp"

EnemyHitboxBehaviour::~EnemyHitboxBehaviour()
{
	enemyPosition = nullptr;
}

void EnemyHitboxBehaviour::OnStart()
{

}

void EnemyHitboxBehaviour::OnUpdate()
{
	if (enemyPosition && transform->gameObject && transform->gameObject->HasComponent<Transform>())
	{
		transform->gameObject->GetComponent<Transform>().position.SetX(enemyPosition->GetX());
		transform->gameObject->GetComponent<Transform>().position.SetY(enemyPosition->GetY());
	}
}

void EnemyHitboxBehaviour::SetEnemyPosition(Math::Vector2* position) 
{
	enemyPosition = position;
}
