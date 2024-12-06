#pragma once

#include "Engine/Delta.hpp"

#include "../Classes/DamageBehaviour.hpp"

class EnemyBehaviour : public BehaviourScript
{
   public:
	~EnemyBehaviour()
	{
		sprite = nullptr;
		rigidbody = nullptr;
		delete _damageBehaviour;
	}

	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

   private:
	DamageBehaviour* _damageBehaviour{nullptr};

	int hp{5};	
};