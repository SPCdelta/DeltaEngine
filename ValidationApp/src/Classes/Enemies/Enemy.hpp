#pragma once

#include "Engine/Delta.hpp"

class Enemy
{
   public:
	Enemy(const Math::Point& start_position, float speed) : position_(start_position), speed_(speed) {}

	virtual void Update(const Math::Point& player_position) = 0;

	Math::Point GetPosition() const { return position_; }

   protected:
	Math::Point position_;
	float speed_;

	void MoveTowards(const Math::Point& target)
	{
		Math::Point direction = GetDirectionTo(target);
		position_.SetX(position_.GetX() + (direction.GetX() * speed_));
		position_.SetY(position_.GetY() + (direction.GetY() * speed_));
	}

	Math::Point GetDirectionTo(const Math::Point& target) const // TODO correct set values?
	{
		Math::Point direction{0, 0};
		if (target.GetX() > position_.GetX())
			direction.SetX(1);
		else if (target.GetX() < position_.GetX())
			direction.SetX(-1);

		if (target.GetY() > position_.GetY())
			direction.SetY(1);
		else if (target.GetY() < position_.GetY())
			direction.SetY(-1);

		return direction;
	}
};
