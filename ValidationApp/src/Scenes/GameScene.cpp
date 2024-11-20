#include "GameScene.hpp"

GameScene::GameScene(const std::string& name) 
	: Scene(name) 
{
	// Create Player
	std::shared_ptr<GameObject> playerObject{ Instantiate({ { 200.0f, 200.0f}, 0.0f, { 64.0f, 64.0f } }) };
	playerObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
	player = playerObject->AddComponent<PlayerBehaviour>();

	Instantiate({ { 200.0f, 200.0f}, 0.0f, { 64.0f, 64.0f } })->AddComponent<TempBehaviour>();

	// ...
	for (size_t y = 0; y < 2; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			std::shared_ptr<GameObject> obj{ Instantiate({{ x * 64.0f, y * 64.0f }, 0.0f, { 64.0f, 64.0f }}) };
			obj->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
		}
	}
}