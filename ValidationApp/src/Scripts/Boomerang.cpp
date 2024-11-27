#include "Boomerang.hpp"

void Boomerang::OnStart() 
{
	gameObject->AddComponent<Sprite>("Assets\\Textures\\player.png");
}

void Boomerang::OnUpdate() 
{
	
}

void Boomerang::Throw(GameObject* thrower, float speed, Math::Vector2 direction)
{
	_thrower = thrower;
}
