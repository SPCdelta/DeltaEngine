#include "GameScene.hpp"

GameScene::GameScene(const std::string& name) 
	: Scene(name) 
{
	// Register Sprites
	SpriteMap floormap
	{
		// 64x64 met 4 sprites
		"floor_map",
		{
			{
				"water",
				"Assets\\Textures\\floor_map.png",
				{ 0.0f, 0.0f },
				{ 32.0f, 32.0f }
			},
			{
				"lava",
				"Assets\\Textures\\floor_map.png",
				{ 32.0f, 0.0f }, 
				{ 64.0f, 32.0f }
			},
			{
				"grass",
				"Assets\\Textures\\floor_map.png",
				{ 0.0f, 32.0f }, 
				{ 32.0f, 64.0f }
			},
			{
				"stone",
				"Assets\\Textures\\floor_map.png",
				{ 32.0f, 32.0f },
				{ 64.0f, 64.0f }
			},
		}
	};

	// Create Player
	std::shared_ptr<GameObject> player{ Instantiate({{3.0f, 6.0f}, 0.0f, {1.0f, 1.0f}}) };
	player->AddComponent<Sprite>("grass");
	player->AddComponent<BoxCollider>();
	player->AddComponent<Rigidbody>();
	player->AddComponent<PlayerBehaviour>();

	size_t mapWidth = 30;
	size_t mapHeight = 18;

	// Create Map
	for (size_t y = 0; y < mapHeight; y++)
	{
		for (size_t x = 0; x < mapWidth; x++)
		{
			std::shared_ptr<GameObject> obj{ Instantiate({{ x * 1.0f, y * 1.0f }, 0.0f, { 1.0f, 1.0f }}) };

			// Ice
			if ((x > 7 && x < 14) && (y > 8 && y < 15))
			{
				obj->AddComponent<Sprite>("water");
				obj->AddComponent<BoxCollider>()->SetTrigger(true);
				obj->SetTag("ice");
			}

			// Mud
			else if ((x > 17 && x < 24) && (y > 12 && y < 16))
			{
				obj->AddComponent<Sprite>("lava");
				obj->AddComponent<BoxCollider>()->SetTrigger(true);
				obj->SetTag("mud");
			}

			// Walls
			else if ((x == 0 || x == mapWidth -1 ) || (y == 0 || y == mapHeight - 1))
			{
				obj->AddComponent<Sprite>("stone");
				obj->AddComponent<BoxCollider>();
			}
			else
			{
				//obj->AddComponent<Sprite>("Assets\\Textures\\stone_floor.png");
			}
		}
	}

	Instantiate({{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}})->AddComponent<MouseFollowBehaviour>();
}