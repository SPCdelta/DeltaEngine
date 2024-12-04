#pragma once

#include "Engine/Delta.hpp"

class FileScene : public Scene
{
   public:
		FileScene(const std::string& name) : Scene(name)
		{
			FileManager fileManager;

			std::shared_ptr<GameObject> playerObject{Instantiate({{200.0f, 200.0f}, 0.0f, {64.0f, 64.0f}})};
			std::shared_ptr<AnimationSheet> sheet = std::make_shared<AnimationSheet>(playerObject->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
			playerObject->AddComponent<Sprite>("spritesheet", sheet);

			// Ice floor
			std::vector<std::shared_ptr<GameObject>> tiles = std::vector<std::shared_ptr<GameObject>>();

			std::shared_ptr<GameObject> iceFloorObj{ Instantiate({{ 10.0f, 10.0f }, 0.0f, { 1.0f, 1.0f }}) };
			iceFloorObj->AddComponent<Sprite>("ice")->SetLayer(Layer::Floor);
			iceFloorObj->AddComponent<BoxCollider>()->SetTrigger(true);
			iceFloorObj->SetTag("ice");
			tiles.push_back(iceFloorObj);

			std::shared_ptr<GameObject> iceFloorObj2{ Instantiate({{ 1.0f, 10.0f }, 0.0f, { 1.0f, 1.0f }}) };
			iceFloorObj2->AddComponent<Sprite>("ice")->SetLayer(Layer::Floor);
			iceFloorObj2->AddComponent<BoxCollider>()->SetTrigger(true);
			iceFloorObj2->SetTag("ice");
			tiles.push_back(iceFloorObj2);

			std::shared_ptr<GameObject> iceFloorObj3{ Instantiate({{ 10.0f, 1.0f }, 0.0f, { 1.0f, 1.0f }}) };
			iceFloorObj3->AddComponent<Sprite>("ice")->SetLayer(Layer::Floor);
			iceFloorObj3->AddComponent<BoxCollider>()->SetTrigger(true);
			iceFloorObj3->SetTag("ice");
			tiles.push_back(iceFloorObj3);

			// Wall
			std::shared_ptr<GameObject> wallObj{ Instantiate({{ 20.0f, 10.0f }, 0.0f, { 1.0f, 1.0f }}) };
			wallObj->AddComponent<Sprite>("stone_wall")->SetLayer(Layer::Walls);
			wallObj->AddComponent<BoxCollider>();
			tiles.push_back(wallObj);

			// Stone floor
			std::shared_ptr<GameObject> stoneFloorObj{ Instantiate({{ 10.0f, 20.0f }, 0.0f, { 1.0f, 1.0f }}) };
			stoneFloorObj->AddComponent<Sprite>("stone_floor")->SetLayer(Layer::Floor);
			tiles.push_back(stoneFloorObj);

			// Saving to file
			Json::json tilesJson;

			int counter = 0;
			for (std::shared_ptr<GameObject> tile : tiles)
			{
				tilesJson["tiles"][counter]["transform"]["position"]["x"] = tile->GetComponent<Transform>().position.GetX();
				tilesJson["tiles"][counter]["transform"]["position"]["y"] = tile->GetComponent<Transform>().position.GetY();
				tilesJson["tiles"][counter]["transform"]["rotation"] = tile->GetComponent<Transform>().rotation;
				tilesJson["tiles"][counter]["transform"]["scale"]["x"] = tile->GetComponent<Transform>().scale.GetX();
				tilesJson["tiles"][counter]["transform"]["scale"]["y"] = tile->GetComponent<Transform>().scale.GetY();

				tilesJson["tiles"][counter]["tag"] = tile->GetTag();

				if (tile->HasComponent<Sprite>())
				{
					tilesJson["tiles"][counter]["sprite"] = tile->GetComponent<Sprite>().GetSprite();
					tilesJson["tiles"][counter]["layer"] = tile->GetLayer();
				}
					
				if (tile->HasComponent<BoxCollider>())
				{
					tilesJson["tiles"][counter]["hasBoxcolider"] = true;
					tilesJson["tiles"][counter]["isTrigger"] = tile->GetComponent<BoxCollider>().IsTrigger();
				}
				else
				{
					tilesJson["tiles"][counter]["hasBoxcolider"] = false;
				}

				counter++;
			}

			fileManager.Save("Assets\\Files\\tiles.json", "json", tilesJson);

			// Loading
			Json::json loadTiles = fileManager.Load("Assets\\Files\\tiles.json", "json");
			std::cout << "Loaded data: " << loadTiles.dump(4) << std::endl;




		}
};
