#pragma once

#include "../UI/BaseUIScene.hpp"

#include "../Scripts/MainMenuBehaviour.hpp"
#include "../Views/MenuView.hpp"

class MainMenuScene : public BaseUIScene
{
public:
	MainMenuScene(const std::string& sceneName);
	void OnStart() override;
};