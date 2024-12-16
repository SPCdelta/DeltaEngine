#pragma once

#include "Engine/Delta.hpp"

class EnemyHitboxBehaviour : public BehaviourScript
{
   public:
	void OnStart() override;
	void OnUpdate() override;

	void SetEnemyPosition(Math::Vector2* position);
	
   private:
	Math::Vector2* enemyPosition;
};