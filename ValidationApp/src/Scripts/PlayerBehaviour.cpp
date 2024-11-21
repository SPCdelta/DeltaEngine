#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
}

void PlayerBehaviour::OnUpdate() 
{
	if (test >= 200)
	{
		LoadScene("MainMenuScene");
	}

	std::cout << "GameScene: " << test << std::endl;
	test++;
}
