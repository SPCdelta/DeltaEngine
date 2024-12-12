#pragma once

#include "Engine/Delta.hpp"

class Enemy
{
   public:
	Enemy(Math::Vector2* position, float speed, int health) : position_(position), speed_(speed), _health(health) {} // TODO keep speed here?

	virtual void Update(const Math::Vector2& player_position) = 0;

	Math::Vector2* GetPosition() const { return position_; }

	int GetHealth() const { return _health; }
	void SetHealth(int health) { _health = health; }

   private:
	int _health;

   protected:
	Math::Vector2* position_;
	float speed_;

	void MoveTowards(const Math::Vector2& target)
	{
		Math::Vector2 direction = GetDirectionTo(target);
		position_->SetX(position_->GetX() + (direction.GetX() * speed_));
		position_->SetY(position_->GetY() + (direction.GetY() * speed_));
	}

	Math::Vector2 GetDirectionTo(const Math::Vector2& target) const // TODO correct set values?
	{
		Math::Vector2 direction{0, 0};
		if (target.GetX() > position_->GetX())
			direction.SetX(1);
		else if (target.GetX() < position_->GetX())
			direction.SetX(-1);

		if (target.GetY() > position_->GetY())
			direction.SetY(1);
		else if (target.GetY() < position_->GetY())
			direction.SetY(-1);

		return direction;
	}
};
