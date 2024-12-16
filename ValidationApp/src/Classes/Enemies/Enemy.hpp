#pragma once

#include "Engine/Delta.hpp"

class Enemy
{
   public:
	Enemy(Math::Vector2* position, float speed, int health) : position_(position), speed_(speed), _health(health) {}

	virtual void Update(const Math::Vector2& player_position) = 0;

	Math::Vector2* GetPosition() const { return position_; }

	int GetHealth() const { return _health; }
	void SetHealth(int health) { _health = health; }

   private:
	int _health;

   protected:
	Math::Vector2* position_;
	float speed_;
};
