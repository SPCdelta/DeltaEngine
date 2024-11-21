#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
}

void PlayerBehaviour::OnUpdate() 
{
	std::cout << "Counter: " << test << std::endl;
	test++;
}
