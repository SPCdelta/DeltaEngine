#pragma once

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(Math::Vector2* position) : Enemy(position, 1.0f, 5, 10, 1) {}

	void Update(const Math::Vector2& player_position, Audio::SFXSource* _sfx) override {}
};