#pragma once

#include "Engine/Delta.hpp"

class FileScene : public Scene
{
   public:
		FileScene(const std::string& name) : Scene(name)
		{
			FileManager fileManager;

			std::shared_ptr<GameObject> playerObject{Instantiate({{200.0f, 200.0f}, 0.0f, {64.0f, 64.0f}})};
			std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(playerObject->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
			playerObject->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", sheet);

			// Loading
			Json::json loadedData1 = fileManager.Load("Assets\\Files\\example.json", "json");
			std::cout << "Loaded data: " << loadedData1.dump(4) << std::endl;

			// Saving/Overwriting
			Json::json dataToSave;
			dataToSave["spritePath"] = playerObject->GetComponent<Sprite>().GetPath();
			fileManager.Save("Assets\\Files\\example.json", "json", dataToSave);

			// Loading
			Json::json loadedData2 = fileManager.Load("Assets\\Files\\example.json", "json");
			std::cout << "Loaded data: " << loadedData2.dump(4) << std::endl;
		}
};
