#pragma once

#include "Engine/Delta.hpp"

class FileScene : public Scene
{
   public:
		FileScene(const std::string& name) : Scene(name)
		{
			FileManager fileManager;

			// Comment this in to save tiles to file (I'd reccomend leaving the loading commented out)
			/*// Ice floor
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
			for (size_t i = 0; i < tiles.size(); ++i)
			{
				auto& tileJson = tilesJson["tiles"][i];

				tileJson["transform"]["position"]["x"] = tiles[i]->GetComponent<Transform>().position.GetX();
				tileJson["transform"]["position"]["y"] = tiles[i]->GetComponent<Transform>().position.GetY();
				tileJson["transform"]["rotation"] = tiles[i]->GetComponent<Transform>().rotation;
				tileJson["transform"]["scale"]["x"] = tiles[i]->GetComponent<Transform>().scale.GetX();
				tileJson["transform"]["scale"]["y"] = tiles[i]->GetComponent<Transform>().scale.GetY();

				tileJson["tag"] = tiles[i]->GetTag();

				if (tiles[i]->HasComponent<Sprite>())
				{
					const auto& sprite = tiles[i]->GetComponent<Sprite>();
					tileJson["sprite"]["name"] = sprite.GetSprite();  
					tileJson["layer"] = static_cast<int>(sprite.GetLayer());
				}
					
				if (tiles[i]->HasComponent<BoxCollider>())
				{
					const auto& collider = tiles[i]->GetComponent<BoxCollider>();
					tileJson["boxCollider"]["isTrigger"] = collider.IsTrigger();
				}
			}

			fileManager.Save("Assets\\Files\\tiles.json", "json", tilesJson);*/

			// Comment this in to load tiles from a file (I'd reccomend leaving the saving commented out)
			/*// Loading
			Json::json loadTiles = fileManager.Load("Assets\\Files\\tiles.json", "json");
			if (loadTiles.contains("tiles"))
			{
				for (size_t i = 0; i < loadTiles["tiles"].size(); ++i)
				{
					auto& tile = loadTiles["tiles"][i];
					if (tile.contains("transform"))
					{
						Transform transform = 
						{
							{
								static_cast<float>(tile["transform"]["position"]["x"]),
								static_cast<float>(tile["transform"]["position"]["y"])
							},
							static_cast<float>(tile["transform"]["rotation"]),
							{
								static_cast<float>(tile["transform"]["scale"]["x"]),
								static_cast<float>(tile["transform"]["scale"]["y"])
							}
						};

						std::shared_ptr<GameObject> obj{ Instantiate(transform) };

						if (tile.contains("sprite"))
						{
							std::string spriteName = tile["sprite"]["name"];
							Layer layer = static_cast<Layer>(tile["layer"]);
							obj->AddComponent<Sprite>(spriteName.c_str())->SetLayer(layer);
						}

						if (tile.contains("boxCollider"))
						{
							bool isTrigger = tile["boxCollider"]["isTrigger"];
							obj->AddComponent<BoxCollider>()->SetTrigger(isTrigger);
						}

						if (tile.contains("tag"))
						{
							obj->SetTag(tile["tag"]);
						}
					}
				}
			}*/
		}
};
