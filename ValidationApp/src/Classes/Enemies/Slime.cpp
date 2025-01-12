#include "Slime.hpp"

Slime::Slime(Math::Vector2* position, bool boss, float speed, int health, int damage, int range, int step)
	: Enemy(position, speed, health, damage, range, step), 
	  _boss(boss)
{

}

void Slime::Update(Transform& player_position, Audio::SFXSource* _sfx) 
{

}

void Slime::Die(Audio::SFXSource* _sfx)
{
	_dead = true;

	if (_sfx)
	{
		_sfx->SetClip("slime_death");
		_sfx->SetVolume(5);
		_sfx->Play();
	}
}