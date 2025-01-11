#include "LevelScene.hpp"

LevelScene::LevelScene(const std::string& name) 
	: Scene(name) 
{

}

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

		// Variables to track map bounds
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::lowest();
		float maxY = std::numeric_limits<float>::lowest();

		auto updateBounds = [&](const Transform& transform)
		{
			float x = transform.position.GetX();
			float y = transform.position.GetY();
			float width = transform.scale.GetX();
			float height = transform.scale.GetY();

			// Update bounds
			minX = std::min(minX, x);
			minY = std::min(minY, y);
			maxX = std::max(maxX, x + width);
			maxY = std::max(maxY, y + height);
		};

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

		playerObject->AddComponent<AStarWalkable>(true, playerObject->GetComponent<Transform>().position);

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
					tileObj->AddComponent<Sprite>(tile["sprite"]["name"])->SetLayer(layer);
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
				}

				tileObj->AddComponent<AStarWalkable>(true, tileObj->GetComponent<Transform>().position);
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

				tileObj->AddComponent<AStarWalkable>(false, tileObj->GetComponent<Transform>().position);
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
					tileObj->AddComponent<EntitySpawner>
					(
						tileObj, 
						EntitySpawnerData
						{
							// Spawn interval
							8.0f,
							10.0f,

							// Spawn amount | OnStart
							2, 3, true,

							// Spawn Radius
							2.5f
						},
						[this, playerObject, enemyName](std::shared_ptr<GameObject>& entity)
						{ 
							std::shared_ptr<AnimationSheet> sheet;
							if (enemyName == "slime")
								sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 3, 24, 24, 1, 3, 0, 2);
							else if (enemyName == "goblin")
								sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 6, 64, 64, 3, 1, 4, 2);
							else if (enemyName == "skeleton")
								sheet = std::make_shared<AnimationSheet>(entity->GetComponent<Transform>(), 9, 64, 64, 1, 3, 2, 4);

							entity->AddComponent<Sprite>(enemyName, sheet)->SetLayer(Layer::Player);
							entity->AddComponent<Audio::SFXSource>("", false, false);
							entity->AddComponent<BoxCollider>()->SetTrigger(true);
							entity->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
							entity->SetTag(enemyName);
							entity->AddComponent<EnemyBehaviour>()->SetPlayer
							(
								&playerObject->GetComponent<Transform>(), 
								playerObject->GetComponent<PlayerBehaviour>().GetPlayer()
							);
						}
					);
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
				}

				tileObj->AddComponent<AStarWalkable>(true, tileObj->GetComponent<Transform>().position);
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
					tileObj->AddComponent<Sprite>(tile["sprite"]["name"])->SetLayer(layer);

					tileObj->AddComponent<LevelExitBehaviour>("LevelSelectScene");
					tileObj->SetTag("level_exit");

					tileObj->AddComponent<AStarWalkable>(false, tileObj->GetComponent<Transform>().position);
				}
			}
		}

		_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
		playerBehaviour->LoadPlayer();

		// Success!
		return true;
	}
	catch (const std::exception&)
	{
		return false;
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
