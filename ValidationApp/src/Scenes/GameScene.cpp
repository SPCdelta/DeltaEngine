#include "GameScene.hpp"

GameScene::GameScene(const std::string& name) 
	: Scene(name) 
{
	// Create Player
	std::shared_ptr<GameObject> player{ Instantiate({{3.0f, 6.0f}, 0.0f, {1.0f, 1.0f}}) };
	player->AddComponent<Sprite>("Assets\\Textures\\player.png");
	player->AddComponent<BoxCollider>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<PlayerBehaviour>();

	// Create Map
	for (size_t y = 0; y < 18; y++)
	{
		for (size_t x = 0; x < 18; x++)
		{
			std::shared_ptr<GameObject> obj{ Instantiate({{ x * 1.0f, y * 1.0f }, 0.0f, { 1.0f, 1.0f }}) };

			if ((y > 8 && y < 15) && (x > 7 && x < 14))
			{
				obj->AddComponent<Sprite>("Assets\\Textures\\ice_floor.png");
				obj->AddComponent<BoxCollider>()->SetTrigger(true);
			}
			else if ((x == 0 || x == 17) || (y == 0 || y == 17))
			{
				obj->AddComponent<Sprite>("Assets\\Textures\\wall.png");
				obj->AddComponent<BoxCollider>();
			}
			else
			{
				obj->AddComponent<Sprite>("Assets\\Textures\\stone_floor.png");
			}
		}
	}
}