#pragma once

#include "Engine/Delta.hpp"

#include "../Classes/Enemies/Enemy.hpp"
#include "../Classes/Enemies/Goblin.hpp"
#include "../Classes/DamageBehaviour.hpp"

class EnemyBehaviour : public BehaviourScript
{
   public:
	~EnemyBehaviour();

	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

	Math::Vector2* playerPosition = nullptr;
	void SetPlayerPosition(Math::Vector2* pos);

	Enemy& GetEnemy() const { return *_enemy; }

	void SetDamageBehaviour(Rigidbody& rigid);

	Events::EventDispatcher<Events::Event> onDeath{};

   private:
	DamageBehaviour* _damageBehaviour{nullptr};
	AIBehaviour* _aiBehaviour{nullptr};

	// Audio
	Audio::SFXSource* _sfx;

	Math::Vector2 _moveDirection{0.0f, 0.0f};

	std::unique_ptr<Enemy> _enemy;
	bool _dead = false;
};