#pragma once

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(Math::Vector2* position) : Enemy(position, 1.0f, 5, 10, 10, 1) {}

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override {}
};
