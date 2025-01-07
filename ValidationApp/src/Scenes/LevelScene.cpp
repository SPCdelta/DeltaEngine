#include "LevelScene.hpp"

void LevelScene::OnStart() 
{
	// Data
	Json::json& data = RetriveUserData();
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

		// 3. Load Tiles (Floor)
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
					tileObj
						->AddComponent<Sprite>(tile["sprite"]["name"])
						->SetLayer(layer);

					//switch (layer)
					//{
					//	case Layer::Wall:
					//		tileObj->AddComponent<BoxCollider>();
					//		break;
					//	default:
					//		break;
					//}
				}

				if (tile.contains("tag"))
				{
					tileObj->SetTag(tile["tag"]);
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

		// 4. Load Enemies


		_hud = std::make_unique<HUDView>(*this, "goblin", playerObject->GetComponent<PlayerBehaviour>().GetPlayer());
		playerBehaviour->LoadPlayer();

		// Success!
		return true;
	}
	catch (const std::exception&)
	{

	}
}