#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(Math::Vector2* position) : Enemy(position, 2.0f, 25, 10, 20, 5) {}

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override {}
};
