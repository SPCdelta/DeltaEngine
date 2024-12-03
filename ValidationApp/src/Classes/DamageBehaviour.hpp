#pragma once

#include "Engine/Delta.hpp"

class DamageBehaviour
{
   public:
		DamageBehaviour(Rigidbody& rigidbody, Sprite& sprite) : _rigidbody{ rigidbody }, _sprite{ sprite }
		{
			_ogColor = sprite.GetColor();

			_rigidbody.onTriggerEnter.Register([this](Collider& collider)
			{ 
				if (CanTakeDamage())
				{
					// Touching an object that hurts
					const std::string& tag{collider.transform.gameObject->GetTag()};
					if (tag == "ouch")
					{
						_inContactWithDamageSource = true;
						_damageCount++;
					}
				}
			});

			_rigidbody.onTriggerExit.Register([this](Collider& collider)
			{
				// No longer touching an object that hurts
				const std::string& tag{collider.transform.gameObject->GetTag()};
				if (tag == "ouch")
				{
					_inContactWithDamageSource = false;
					_damageCount--;
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
					_sprite.SetColor(Rendering::Color(255.0f, 255.0f, 255.0f, 1.5f)); // Flash effect
			}
			else
			{
				_sprite.SetColor(_ogColor);	 // Reset color after taking damage
			}
		}

		bool GetDamage() const
		{
			if (_damageCount > 0 && CanTakeDamage() && _inContactWithDamageSource)
				return true;
			return false;
		}

		void TakeDamage()
		{
			StartInvincibility();
			_sprite.SetColor(Rendering::Color(255.0f, 0.0f, 0.0f, 1.0f)); 
		}

	private:
		Rigidbody& _rigidbody;
		Sprite& _sprite;
		Rendering::Color _ogColor;

		int _damageCount{0};
		bool _damage{false};

		bool _inContactWithDamageSource{false};

		float _invincibleTime{0.0f};
		const float _invincibilityDuration = 1.0f; // 1 second of invincibility

		void StartInvincibility()
		{
			_invincibleTime = _invincibilityDuration;
		}

		bool CanTakeDamage() const
		{
			return _invincibleTime <= 0.0f;
		}
};