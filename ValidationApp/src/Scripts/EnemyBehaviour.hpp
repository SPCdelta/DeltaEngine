#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"
#include "../Classes/DamageBehaviour.hpp"

class EnemyBehaviour : public BehaviourScript
{
   public:
	~EnemyBehaviour()
	{
		sprite = nullptr;
		rigidbody = nullptr;
		delete _damageBehaviour;
		delete _aiBehaviour;
		playerPosition = nullptr;
	}

	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

	Math::Vector2* playerPosition = nullptr;
	void SetPlayerPosition(Math::Vector2* pos);

   private:
	DamageBehaviour* _damageBehaviour{nullptr};
	AIBehaviour* _aiBehaviour{nullptr};

	Math::Vector2 _moveDirection{0.0f, 0.0f};

	int hp{5};	
};