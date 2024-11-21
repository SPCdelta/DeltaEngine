#pragma once

#include "Engine/Delta.hpp"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(const std::string& sceneName)
		: Scene(sceneName)
	{
		std::shared_ptr<GameObject> menuImage{Instantiate({{0.0f, 0.0f}, 0.0f, {200.0f, 200.0f}})};
		menuImage->AddComponent<Sprite>("Assets\\Textures\\spritesheet.png");
	}
};