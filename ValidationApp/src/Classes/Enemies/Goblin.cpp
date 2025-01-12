#include "Goblin.hpp"

Goblin::Goblin(Math::Vector2* position, float speed, int health, int damage, int range, int step)
	: Enemy(position, speed, health, damage, range, step)
{

}

void Goblin::Update(Transform& player_position, Audio::SFXSource* _sfx)
{

}

void Goblin::Die(Audio::SFXSource* _sfx)
{
	_dead = true;

	if (_sfx)
	{
		_sfx->SetClip("goblin_death");
		_sfx->SetVolume(3);
		_sfx->Play();
	}
}