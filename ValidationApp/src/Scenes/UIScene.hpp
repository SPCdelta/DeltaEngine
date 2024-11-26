#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/TempBehaviour.hpp"

class UIScene : public Scene
{
   public:
	UIScene(const std::string& name) : Scene(name)
	{
		Instantiate({{200.0f, 400.0f}, 0.0f, {100.0f, 150.0f}})->AddComponent<Image>("Assets\\Textures\\default_texture.png")->SetColor({255, 255, 255, 255});
	}
};