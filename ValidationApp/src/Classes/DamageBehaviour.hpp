#pragma once

#include "Engine/Delta.hpp"

class DamageBehaviour
{
   public:
		DamageBehaviour(Rigidbody& rigidbody, Sprite& sprite, const std::string& damageSourceTag) : _rigidbody{ rigidbody }, _sprite{ sprite }, _damageSourceTag{ damageSourceTag }
		{
			_ogColor = sprite.GetColor();

			_rigidbody.onTriggerEnter.Register([this](Collider& collider)
			{ 
				if (CanTakeDamage())
				{
					if (collider.transform.gameObject->GetTag() == _damageSourceTag)
					{
						_damageCount = 1;
					}
				}
			});

			_rigidbody.onTriggerExit.Register([this](Collider& collider)
			{
				if (collider.transform.gameObject->GetTag() == _damageSourceTag)
				{
					_damageCount = 0;
				}
			});
		}

		~DamageBehaviour()
		{
			// TODO unregister events
		}

		void Update(float deltaTime)
		{
			if (_invincibleTime > 0.0f)
			{
				_invincibleTime -= deltaTime;
				if (static_cast<int>(_invincibleTime * 10) % 2 == 0)
					_sprite.SetColor(_ogColor);	 // Normal color
				else
					_sprite.SetColor(Rendering::Color(255, 255, 255)); // Flash effect
			}
			else
			{
				_sprite.SetColor(_ogColor);	 // Reset color after taking damage
			}
		}

		bool GetDamage() const
		{
			return _damageCount > 0 && CanTakeDamage();
		}

		void TakeDamage()
		{
			StartInvincibility();
			_sprite.SetColor(Rendering::Color(255,0,0)); 
		}

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;
		std::string _damageSourceTag;

		Rendering::Color _ogColor;

		int _damageCount{0};

		float _invincibleTime{0.0f};
		const float _invincibilityDuration = 1.0f; // 1 second of invincibility

		void StartInvincibility()
		{
			_invincibleTime = _invincibilityDuration / Time::GetMultiplier();
		}

		bool CanTakeDamage() const
		{
			return _invincibleTime <= 0.0f;
		}
};