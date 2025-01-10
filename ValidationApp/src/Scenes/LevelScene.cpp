#include "LevelScene.hpp"

void LevelScene::OnStart() 
{
	// Data
	Json::json& data = RetrieveUserData();
	std::string levelName = data["levelName"];

	std::cout << levelName << std::endl;

	if (!LoadLevel(levelName))
	{
		std::cerr << "Level could not be loaded" << std::endl;
		LoadScene("LevelSelectScene");
		return;
	}
}

bool LevelScene::LoadLevel(const std::string& levelName) 
{
	try
	{
		// 1. Get File
		FileManager fileManager{};
		Json::json file = fileManager.Load("Assets\\Level\\" + levelName, "json");

		// 2. Load Player
		if (!file.contains(PlayerName))
			return false;

		auto& playerDto = file[PlayerName];
		std::shared_ptr<GameObject> playerObject
		{ 
			Instantiate
			(
				Transform
				{
					{ static_cast<float>(playerDto["transform"]["position"]["x"]), static_cast<float>(playerDto["transform"]["position"]["y"]) },
					static_cast<float>(playerDto["transform"]["rotation"]),
					{ static_cast<float>(playerDto["transform"]["scale"]["x"]), static_cast<float>(playerDto["transform"]["scale"]["y"]) }
				}
			) 
		};
		std::shared_ptr<AnimationSheet> playerSheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 9, 64, 64, 9, 11, 10, 12);
		playerSheet->AddCustomAnimation("death", 6, 21, 150);

		playerObject->AddComponent<Sprite>("layerPlayer", playerSheet)->SetLayer(Layer::Player);
		playerObject->AddComponent<Audio::SFXSource>("", false, false);
		playerObject->AddComponent<BoxCollider>();
		playerObject->AddComponent<Rigidbody>();	
		auto playerBehaviour = playerObject->AddComponent<PlayerBehaviour>();
		playerObject->SetTag("player");

		// Load Tiles (Floor)
		{
			if (!file.contains(FloorTilesName))
				return false;

			for (size_t i = 0; i < file[FloorTilesName].size(); i++)
			{
				auto& tile = file[FloorTilesName][i];

				// Transform
				if (!tile.contains("transform"))
					return false;

				std::shared_ptr<GameObject> tileObj = Instantiate
				(
					Transform
					{
						{ static_cast<float>(tile["transform"]["position"]["x"]), static_cast<float>(tile["transform"]["position"]["y"]) },
						static_cast<float>(tile["transform"]["rotation"]),
						{ static_cast<float>(tile["transform"]["scale"]["x"]), static_cast<float>(tile["transform"]["scale"]["y"]) }
					}
				);

				if (tile.contains("sprite"))
				{
					Layer layer = static_cast<Layer>(static_cast<int>(tile["sprite"]["layer"]));
					tileObj->AddComponent<Sprite>(tile["sprite"]["name"])
						->SetLayer(layer);
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
					if (tile["tag"] == "Ice")
					{
						tileObj->SetTag("ice");
						tileObj->AddComponent<BoxCollider>()->SetTrigger(true);
					}
					else if (tile["tag"] == "Mud")
					{
						tileObj->SetTag("mud");
						tileObj->AddComponent<BoxCollider>()->SetTrigger(true);
					}
				}
			}
		}

		// Load Tiles (Walls)
		{
			if (!file.contains(WallTilesName))
				return false;

			for (size_t i = 0; i < file[WallTilesName].size(); i++)
			{
				auto& tile = file[WallTilesName][i];

				// Transform
				if (!tile.contains("transform"))
					return false;

				std::shared_ptr<GameObject> tileObj = Instantiate
				(
					Transform
					{
						{ static_cast<float>(tile["transform"]["position"]["x"]), static_cast<float>(tile["transform"]["position"]["y"]) },
						static_cast<float>(tile["transform"]["rotation"]),
						{ static_cast<float>(tile["transform"]["scale"]["x"]), static_cast<float>(tile["transform"]["scale"]["y"]) }
					}
				);

				if (tile.contains("sprite"))
				{
					Layer layer = static_cast<Layer>(static_cast<int>(tile["sprite"]["layer"]));
					tileObj->AddComponent<Sprite>(tile["sprite"]["name"])->SetLayer(layer);
					tileObj->AddComponent<BoxCollider>();
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
				}
			}
		}

		// Load Enemies
		{
			if (!file.contains(EnemySpawnersName))
				return false;

			for (size_t i = 0; i < file[EnemySpawnersName].size(); i++)
			{
				auto& tile = file[EnemySpawnersName][i];

				// Transform
				if (!tile.contains("transform"))
					return false;

				std::shared_ptr<GameObject> tileObj = Instantiate
				(
					Transform
					{
						{ static_cast<float>(tile["transform"]["position"]["x"]), static_cast<float>(tile["transform"]["position"]["y"]) },
						static_cast<float>(tile["transform"]["rotation"]),
						{ static_cast<float>(tile["transform"]["scale"]["x"]), static_cast<float>(tile["transform"]["scale"]["y"]) }
					}
				);

				if (tile.contains("sprite"))
				{
					std::string spriteName = tile["sprite"]["name"];
					std::string enemyName = GetEnemyName(spriteName);
					Layer layer = Layer::Floor;
					Sprite* sprite = tileObj->AddComponent<Sprite>(tile["sprite"]["name"]);
					sprite->SetLayer(layer);
					tileObj->AddComponent<EntitySpawner>(
							tileObj, EntitySpawnerData
							{
								// Spawn interval
								60.0f,
								70.0f,

								// Spawn amount | OnStart
								2, 3, true,

								// Spawn Radius
								2.5f
							},
							[this, playerObject, enemyName](std::shared_ptr<GameObject>& entity)
							{ 
								std::shared_ptr<AnimationSheet> sheet;
								if (enemyName == "slime")
								{
									sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 3, 24, 24, 1, 3, 0, 2);
								}
								else if (enemyName == "goblin")
								{
									sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 6, 64, 64, 3, 1, 4, 2);
								}
								else if (enemyName == "skeleton")
								{
									sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 9, 64, 64, 1, 3, 2, 4);
								}
								entity->AddComponent<Sprite>(enemyName, sheet)->SetLayer(Layer::Player);
								entity->AddComponent<Audio::SFXSource>("", false, false);
								entity->AddComponent<BoxCollider>()->SetTrigger(true);
								entity->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
								entity->SetTag(enemyName);
								entity
									->AddComponent<EnemyBehaviour>()
									->SetPlayer
									(
										&playerObject->GetComponent<Transform>(), 
										playerObject->GetComponent<PlayerBehaviour>().GetPlayer()
									);
							});
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
				}
			}
		}

		// Load Potions
		{
			if (!file.contains(PotionName))
				return false;

			for (size_t i = 0; i < file[PotionName].size(); i++)
			{
				auto& potion = file[PotionName][i];

				// Transform
				if (!potion.contains("transform"))
					return false;

				std::shared_ptr<GameObject> potionObj = Instantiate
				(
					Transform
					{
						{ static_cast<float>(potion["transform"]["position"]["x"]), static_cast<float>(potion["transform"]["position"]["y"]) },
						static_cast<float>(potion["transform"]["rotation"]),
						{ static_cast<float>(potion["transform"]["scale"]["x"]), static_cast<float>(potion["transform"]["scale"]["y"]) }
					}
				);

				if (potion.contains("sprite"))
				{
					Layer layer = static_cast<Layer>(static_cast<int>(potion["sprite"]["layer"]));
					potionObj
						->AddComponent<Sprite>(potion["sprite"]["name"])
						->SetLayer(layer);

					WorldItem potionItem = WorldItem(
						PotionFactory::CreatePotion(StringUtils::ToLower(std::string{potion["tag"]}), 
							10.f, potion["sprite"]["name"], potion["sprite"]["name"], 50.f).release(), 1);
					potionObj->AddComponent<BoxCollider>()->SetTrigger(true);
					potionObj->AddComponent<WorldItem>(potionItem);
					potionObj->SetTag("item");
				}
			}
		}

		// Load Level Exits
		{
			if (!file.contains(LevelExitName))
				return false;

			for (size_t i = 0; i < file[LevelExitName].size(); i++)
			{
				auto& tile = file[LevelExitName][i];

				// Transform
				if (!tile.contains("transform"))
					return false;

				std::shared_ptr<GameObject> tileObj = Instantiate
				(
					Transform
					{
						{ static_cast<float>(tile["transform"]["position"]["x"]), static_cast<float>(tile["transform"]["position"]["y"]) },
						static_cast<float>(tile["transform"]["rotation"]),
						{ static_cast<float>(tile["transform"]["scale"]["x"]), static_cast<float>(tile["transform"]["scale"]["y"]) }
					}
				);

				if (tile.contains("sprite"))
				{
					Layer layer = static_cast<Layer>(static_cast<int>(tile["sprite"]["layer"]));
					tileObj
						->AddComponent<Sprite>(tile["sprite"]["name"])
						->SetLayer(layer);

					tileObj->AddComponent<LevelExitBehaviour>("LevelSelectScene");
					tileObj->SetTag("level_exit");
				}
			}
		}

		_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
		playerBehaviour->LoadPlayer();

		// Success!
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

std::string LevelScene::GetEnemyName(const std::string& spawnerName)
{
	std::string delimiter = "_";

	std::size_t pos = spawnerName.find(delimiter);
	if (pos != std::string::npos)
	{
		return spawnerName.substr(pos + 1);
	}
	else
	{
		return "";
	}
}
