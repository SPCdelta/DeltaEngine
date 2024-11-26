#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidody = &gameObject->GetComponent<Rigidbody>();
}

void PlayerBehaviour::OnUpdate() 
{
	
}
