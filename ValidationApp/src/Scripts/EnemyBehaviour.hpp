#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/EnemyHitboxBehaviour.hpp"
#include "../Classes/Enemies/Enemy.hpp"
#include "../Classes/Enemies/Goblin.hpp"
#include "../Classes/Enemies/Skeleton.hpp"
#include "../Classes/Enemies/Slime.hpp"

class DamageBehaviour;

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

	void OnDeath();


   private:
	std::unique_ptr<DamageBehaviour> _damageBehaviour;
	std::unique_ptr<AIBehaviour> _aiBehaviour;

	std::shared_ptr<GameObject> _damageObj;

	// Audio
	Audio::SFXSource* _sfx;

	Math::Vector2 _moveDirection{0.0f, 0.0f};

	std::unique_ptr<Enemy> _enemy;

	void UpdateAnimation();
};