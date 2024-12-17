#pragma once

#include "Engine/Delta.hpp"

#include "../Player.hpp"
#include "../Classes/Projectiles/Projectile.hpp"

class EnemyBehaviour;

class DamageBehaviour
{
   public:
		DamageBehaviour(Rigidbody& rigidbody, Sprite& sprite, const std::vector<std::string>& damageSourceTags);
		~DamageBehaviour();

		void Update(float deltaTime);

		bool GetDamage() const;
		int TakeDamage();

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;

		Rendering::Color _ogColor;

		Collider* _currentCollider;
		std::vector<std::string> _damageSourceTags;

		int _damageCount{0};

		float _invincibleTime{0.0f};
		const float _invincibilityDuration = 1.0f; // 1 second of invincibility

		void StartInvincibility();
		bool CanTakeDamage() const;
		bool IsDamageSource(const std::string& tag) const;
};