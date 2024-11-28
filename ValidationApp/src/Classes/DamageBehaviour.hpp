#pragma once

#include "Engine/Delta.hpp"

class DamageBehaviour
{
   public:
		DamageBehaviour(Rigidbody& rigidbody) : _rigidbody{ rigidbody }
		{
			_rigidbody.onTriggerEnter.Register([this](Collider& collider)
			{ 
				// TODO iframes
				/*if (CanTakeDamage())
				{*/
					const std::string& tag{collider.transform.gameObject->GetTag()};
					if (tag == "ouch")
					{
						_damageCount++;
						//StartInvincibility();
					}
				//}
			});

			rigidbody.onTriggerExit.Register([this](Collider& collider)
			{
				const std::string& tag{collider.transform.gameObject->GetTag()};
				if (tag == "ouch")
				{
					_damageCount--;
				}
			});
		}

		~DamageBehaviour()
		{
			// TODO
			/*_rigidbody.onTriggerEnter.Unregister(this);
			_rigidbody.onTriggerExit.Unregister(this);*/
		}

		// TODO iframes
		/*void Update(float deltaTime)
		{
			if (_invincibleTime > 0.0f)
			{
				_invincibleTime -= deltaTime;
			}
		}*/

		int GetDamage() const
		{
			if (_damageCount > 0 /*&& CanTakeDamage()*/)
				return -5;
			else
				return 0;
		
		}

	private:
		Rigidbody& _rigidbody;

		int _damageCount{0};

		float _invincibleTime;
		const float _invincibilityDuration = 1.0f; // 1 seconds of invincibility

		void StartInvincibility()
		{
			_invincibleTime = _invincibilityDuration;
		}

		// TODO iframes
		/*bool CanTakeDamage() const
		{
			return _invincibleTime <= 0.0f;
		}*/
};