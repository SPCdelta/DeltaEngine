#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(Math::Vector2* position) : Enemy(position, 2.0f, 15, 20, 5) {}

	void Update(const Math::Vector2& player_position, Audio::SFXSource* _sfx) override {}
};