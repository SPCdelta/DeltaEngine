#pragma once

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(Math::Vector2* position, bool boss = false, float speed = 1.0f, int health = 5, int damage = 10, int range = 10, int step = 1) 
		: Enemy(position, speed, health, damage, range, step), _boss(boss) 
	{}

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override {}

	void Die(Audio::SFXSource* _sfx) override
    {
        _dead = true;
		_sfx->SetClip("Assets\\Audio\\SFX\\Slime_death.mp3");
		_sfx->Play();
    }

   private:
	bool _boss;
};
