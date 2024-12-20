#pragma once

#include "Engine/Delta.hpp"

#include "../Scripts/MainMenuBehaviour.hpp"
#include "../Views/MenuView.hpp"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(const std::string& sceneName);
	void OnStart() override;
};