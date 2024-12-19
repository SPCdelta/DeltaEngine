#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(Math::Vector2* position, float speed = 2.0f, int health = 25, int damage = 10, int range = 20, int step = 5) 
		: Enemy(position, speed, health, damage, range, step) {}

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override {}

	void Die(Audio::SFXSource* _sfx) override
    {
        _dead = true;
		_sfx->SetClip("Assets\\Audio\\SFX\\Goblin_death_1.mp3");
		_sfx->Play();
    }
};
