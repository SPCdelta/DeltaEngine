#pragma once

#include "Engine/Delta.hpp"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(const std::string& sceneName)
		: Scene(sceneName)
	{
		std::shared_ptr<GameObject> menuImage{Instantiate({{0.0f, 0.0f}, 0.0f, {200.0f, 200.0f}})};
		std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(menuImage->GetComponent<Transform>(), 4, 64, 64, 4, 1, 2, 3);
		menuImage->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png", sheet);
	}
};